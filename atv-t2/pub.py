#!/usr/bin/python3

from pika import BlockingConnection
import os
import time

nome_fila = 'filaTasi'

conexao = BlockingConnection()
canal = conexao.channel()
canal.exchange_declare(exchange='newExc', exchange_type='topic')

def getMessageType(msg):
    result = ''
    routing = ''
    splitted = msg.split(":")
    if len(splitted) ==  2:
        if splitted[0] == "verbose":
            result = msg
        else:
            timestamp = time.time()
            pid = os.getpid()
            routing = "log.{0}.{1}".format(pid, splitted[0])
            result = "{0}:{1}:{2}:{3}".format(int(timestamp), splitted[0].upper(), pid, splitted[1])
    else:
        print("Mensagem no formato errado")
    return result, routing

GREEN = '\033[92m'
WHITE = '\033[0m'

# Processo para envio de mensagem
working = True
while working:
    msg = input("Escreva uma mensagem: ")
    working = msg != 'sair'
    if working:
        msg = getMessageType(msg)
        print(f"{GREEN}{msg[0]}, {msg[1]}{WHITE}")
        canal.basic_publish(
            exchange='newExc',
            routing_key=msg[1],
            body=msg[0]
        )

conexao.close()
