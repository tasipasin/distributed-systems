#!/usr/bin/python3

from pika import BlockingConnection
import os
import time

nome_fila = 'filaTasi'

conexao = BlockingConnection()
canal = conexao.channel()
canal.exchange_declare(exchange='sdc', exchange_type='fanout')

# Processo para envio de mensagem
working = True
while working:
    msg = input("Escreva uma mensagem: ")
    working = msg != 'sair'
    timestamp = time.time()
    sev = "INFO"
    pid = os.getpid()
    if working:
        canal.basic_publish(
            exchange='sdc',
            routing_key='',
            body=msg
        )
    i += 1

conexao.close()
