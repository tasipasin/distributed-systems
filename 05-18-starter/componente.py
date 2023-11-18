#!/usr/bin/python3

from pika import BlockingConnection
from sys import argv

if len(argv) < 3:
    print(f"Uso: {argv[0]} <ID> <RelogioInit> [<proxVizi>]")
    exit(1)

idx = argv[1]
R = int(argv[2])
# pode ser uma lista vazia
prox = argv[3:]

def callback(ch, method, properties, body):
    msg = body.decode()
    print("Recebido: ", msg)
    for v in prox:
        envia(msg, v)

def envia(msg, dst):
    canal.basic_publish(
        exchange='',
        routing_key=dst,
        body=msg
    )

conexao = BlockingConnection()
canal = conexao.channel()
canal.queue_declare(queue=idx, auto_delete=True)
for v in prox:
    canal.queue_declare(queue=v, auto_delete=True)
canal.basic_consume(
    queue=idx,
    on_message_callback=callback,
    auto_ack=True
)

try:
    print("Esperando mensagens... CTRL+C para sair")
    canal.start_consuming()
except:
    canal.stop_consuming()
conexao.close()
