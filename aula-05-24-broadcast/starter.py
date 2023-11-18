#!/usr/bin/env python3

# SDC
# Prof. Luiz Lima Jr.

from pika import BlockingConnection
from sys import argv

if len(argv)<3:
    print(f'Uso: {argv[0]} <dest> <mensagem>')
    exit(1)

fila = argv[1]
msg = f'STARTER:{argv[2]}'

conexao = BlockingConnection()
canal = conexao.channel()

canal.queue_declare(queue=fila, auto_delete=True)

canal.basic_publish(exchange = "",
                    routing_key = fila,
                    body = msg)
print(f'"{msg}" enviada para {fila}')
conexao.close()

