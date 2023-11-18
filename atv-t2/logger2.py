#!/usr/bin/python3

from pika import BlockingConnection

exc_name = 'newExc'
verbose = False

def isVerbose():
    global verbose
    return verbose

def setVerbose(value):
    global verbose
    verbose = value

def callback(ch, method, properties, body):
    splitted_str = body.decode().split(":")
    if(len(splitted_str) > 0):
        if splitted_str[0].lower() == "verbose":
            interpretVerbose(splitted_str)
        else:
            interpretMessage(body.decode())

def interpretVerbose(splitted_str):
    if len(splitted_str) == 2:
        verbose_value = True if splitted_str[1].lower() == "on" else False
        print(f"Received to change verbose to {verbose_value}")
        setVerbose(verbose_value)
    else:
        print("Parâmetros incorretos para o comando 'verbose'")

def interpretMessage(message):
    if isVerbose():
        print(message.replace('.', ':'))

conexao = BlockingConnection()
canal = conexao.channel()
canal.exchange_declare(exchange=exc_name, exchange_type='topic')
res = canal.queue_declare(queue='', exclusive=True)
name_queue = res.method.queue
print(f"Nome da fila: {name_queue}")
canal.queue_bind(exchange=exc_name, queue=name_queue, routing_key="#")
canal.basic_consume(
    queue=name_queue,
    on_message_callback=callback, auto_ack=True
)

try:
    print("Esperando mensagens... CTRL+C para sair")
    canal.start_consuming()
except:
    canal.stop_consuming()
conexao.close()
print("Fim")
