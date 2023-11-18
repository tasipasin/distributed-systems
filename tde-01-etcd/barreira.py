#!/usr/bin/env python3

import time
import random
import etcd3
import sys
import logging

# Define a chave do contador de processos encerrados
KEY="/barreiraTasi"
# Quantidade de processos necessários para encerrar
PROCESSES=0
# Indica finalização do processo
END=False
# Define o cliente do etcd3
CLIENT=etcd3.client()

#Definição do log
FORMAT="%(funcName)s:%(lineno)s | %(message)s"
logging.basicConfig(level=logging.INFO, format=FORMAT)

# Retorna a chave do contador
def getKey():
    global KEY
    return KEY

# Retorna a quantidade de processos necessários
# para encerrar
def getProcesses():
    global PROCESSES
    return PROCESSES

# Determina a quantidade de processos necessários
# para encerrar
def setProcesses(value):
    global PROCESSES
    PROCESSES = value

# Retorna indicador para encerrar
def isEnd():
    global END
    return END

#Define indicador para encerrar
def setEnd(value):
    global END
    END = value

# Detorna o client do etcd
def getClient():
    global CLIENT
    return CLIENT

# Método acionado ao receber atualização na chave
def keyEvent(event):
    # Recupera o evento
    valueReceived = event.events[0]
    # Verifica se é do tipo de inserção/atualização
    if isinstance(valueReceived, etcd3.events.PutEvent):
        logging.debug("Recebido evento de inserção")
        # Recupera o valor da chave, no formato string
        value = valueToStr(valueReceived.value)
        logging.debug("Value altered to [{0}]".format(value))
        # Determina o encerramento verificando se o valor
        # recebido é igual à quantidade de processos determinados
        setEnd(valueToInt(value) == getProcesses())

# Processo de criação da chave
def createKey():
    # Recupera a chave
    key = getKey()
    # Recupera o valor da chave
    value = getClient().get(key)
    # Verifica se o valor da chave é None, indicando que não existe
    if value[0] == None:
        logging.debug("creating key [{0}]".format(key))
        # Cria a chave
        getClient().put(key, str(0))
    watchKey()

# Retorna o valor armazenado na chave informada via parâmetro
# como um inteiro. Caso contrário, retorna None
def getValueStoredAsInt(key):
    return valueToInt(getValueStored(key))

# Realiza conversão do valor para numérico, se for
# possível. Caso contrário, retorna None
def valueToInt(value):
    result = None
    # Verifica se o valor recebido não é None
    # e se é um númerico
    if value != None and value.isnumeric():
        result = int(value)
    return result

# Retorna o valor como String decodificado em UTF-8.
# Caso contrário, retorna None
def valueToStr(value):
    result = None
    if value != None:
        result = value.decode('utf-8')
    return result

# Retorna o valor armazenado na chave
def getValueStored(key):
    result = None
    # Recupera o valor da chave
    value = getClient().get(key)
    if value is not None:
        result = valueToStr(value[0])
        logging.debug("recovered value {0} from key {1}".format(result, key))
    return result

# Define um método como callback para qualquer ação na chave
def watchKey():
    # Determina para ficar observando a chave
    getClient().add_watch_callback(getKey(), callback=keyEvent)

# Atualiza o valor da chave, incrementando por 1.
def updateKey():
    key = getKey()
    value = getValueStoredAsInt(key)
    if value != None:
        # Incrementa o valor na chave
        newValue = value + 1
        logging.debug("updating value from {0} to {1}".format(value, newValue))
        getClient().put(key, str(newValue))

def execute():
    for i in range(1, 11):
        print(i)
        if i != 10:
            timeToSleep = 1 * random.random()
            logging.debug("sleeping {0} seconds".format(timeToSleep))
            time.sleep(timeToSleep)

def waitBarrierToEnd():
    while not isEnd():
        time.sleep(0.5)
    print("Passou a barreira")
    getClient().delete(getKey())

# Recupera a quantidade de Processos
# informado via linha de comando
# Retorna -1 para valor não informado
def parameterProcessQtd():
    result = -1
    if len(sys.argv) > 1:
        value = sys.argv[1]
        if value.isnumeric():
            result = int(value)
    setProcesses(result)

def main():
    # Recupera valor do parâmetro (qtd de processos)
    parameterProcessQtd()
    logging.debug("received {0} by param".format(getProcesses()))
    try:
        if getProcesses() > 0:
            createKey()
            execute()
            print("Chegou na barreira...")
            updateKey()
            waitBarrierToEnd()
    except:
        logging.error(sys.exc_info()[0])

if __name__ == "__main__":
    main()
