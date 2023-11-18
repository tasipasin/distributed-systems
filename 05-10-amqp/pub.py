#!/usr/bin/python3

from pika import BlockingConnection
import os
import time

nome_fila = 'filaTasi'

conexao = BlockingConnection()
canal = conexao.channel()
canal.queue_declare(queue=nome_fila)
working = True
while working:
    msg = input("Escreva uma mensagem: ")
    working = msg != 'sair'
    timestamp = time.time()
    sev = "INFO"
    pid = os.getpid()
    if working:
        canal.basic_publish(
            exchange='',
            routing_key=nome_fila,
            body="{timestamp}:{sev}:{pid}:{msg}".format(timestamp, sev, pid, msg)
        )

conexao.close()
