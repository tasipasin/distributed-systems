#!/usr/bin/env python3

from pika import BlockingConnection
from sys import argv

if len(argv) < 3:
    print(f'Uso: {argv[0]} <id> <Rinicial> [<prox>]')
    exit(1)

idx = argv[1]
R = int(argv[2])
Nx = argv[3:]  # vizinhos do componente

def incrementClock():
    global R
    R += 1

def getClock():
    global R
    return R

def incAndGetClock():
    incrementClock()
    return getClock()

def setClock(value):
    global R
    R = value

conexao = BlockingConnection()
canal = conexao.channel()

canal.queue_declare(queue=idx, auto_delete=True)
for v in Nx:
    canal.queue_declare(queue=v, auto_delete=True)

def envia(msg, dest):
    canal.basic_publish(exchange='',
                        routing_key=dest,
                        body="{0}:{1}".format(incAndGetClock(), msg))

def trata_msg(canal, metodo, props, corpo):
    msg = corpo.decode()
    received_clock = 0
    value = msg.split(':')[0]
    if value.isnumeric():
        clock = int(value)
        if clock > getClock():
            setClock(clock)
        else:
            incrementClock()
        print(f"msg recebida:{msg} -> clock: {getClock()}")
        for v in Nx:
            envia(msg, v)
    else:
        print(f"Recebida mensagem errada: {msg}")

canal.basic_consume(queue=idx,
                    on_message_callback=trata_msg,
                    auto_ack=True)
try:
    print(f"aguardando mensagens na fila {idx}")
    canal.start_consuming()
except KeyboardInterrupt:
    canal.stop_consuming()

conexao.close()
print("\nfim")
