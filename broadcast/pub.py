#!/usr/bin/python3

from pika import BlockingConnection
import os
import time
import random

exc_name = 'excTasi'

conexao = BlockingConnection()
canal = conexao.channel()
canal.exchange_declare(exchange=exc_name, exchange_type='fanout')

sev_list = ['DEBUG', 'INFO', 'WARNING', 'ERROR', 'CRITICAL']

# Processo para envio de mensagem
working = True
while working:
    msg = input("Escreva uma mensagem: ")
    working = msg != 'sair'
    if working:
        timestamp = time.time()
        sev = random.choice(sev_list)
        pid = os.getpid()
        msg = "{0}:{1}:{2}:{3}".format(timestamp, sev, pid, msg)
        print(msg)
        canal.basic_publish(
            exchange=exc_name,
            routing_key='',
            body=msg
        )

conexao.close()
