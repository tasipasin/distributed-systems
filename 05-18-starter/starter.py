#!/usr/bin/python3

from pika import BlockingConnection
from sys import argv

if len(argv) < 2:
    print(f"Uso: {argv[0]} <fila>")
    exit(1)
    
nome_fila = argv[1]

conexao = BlockingConnection()
canal = conexao.channel()
canal.queue_declare(queue=nome_fila, auto_delete=True)
working = True
while working:
    msg = input("Escreva uma mensagem: ")
    working = msg != 'sair'
    if working:
        canal.basic_publish(
            exchange='',
            routing_key=nome_fila,
            body=msg
        )

conexao.close()
