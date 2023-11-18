#!/usr/bin/python3

from pika import BlockingConnection

def callback(ch, method, properties, body):
    print("Recebido: ", body.decode())

nome_fila = 'filaTasi'

conexao = BlockingConnection()
canal = conexao.channel()
canal.queue_declare(queue=nome_fila)
canal.basic_consume(
    queue=nome_fila,
    on_message_callback=callback, auto_ack=True
)

try:
    print("Esperando mensagens... CTRL+C para sair")
    canal.start_consuming()
except:
    canal.stop_consuming()
conexao.close()
