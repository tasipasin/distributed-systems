#!/usr/bin/env python3

from pika import BlockingConnection
from sys import argv

if len(argv) < 3:
    print(f'Uso: {argv[0]} <id> <Rinicial> [<prox>]')
    exit(1)

idx = argv[1]
R = int(argv[2])
Nx = argv[3:]  # vizinhos do componente

conexao = BlockingConnection()
canal = conexao.channel()

canal.queue_declare(queue=idx, auto_delete=True)
for v in Nx:
    canal.queue_declare(queue=v, auto_delete=True)

def envia(msg, dest):
    canal.basic_publish(exchange='',
                        routing_key=dest,
                        body=msg)

def trata_msg(canal, metodo, props, corpo):
    msg = corpo.decode()
    print("msg recebida:", msg)
    for v in Nx:
        envia(msg, v)


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
