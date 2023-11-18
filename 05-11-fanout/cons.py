#!/usr/bin/python3

from pika import BlockingConnection

def callback(ch, method, properties, body):
    print("Recebido: ", body.decode())

exc_name = 'excTasi'

conexao = BlockingConnection()
canal = conexao.channel()
canal.exchange_declare(exchange=exc_name, exchange_type='fanout')
res = canal.queue_declare(queue='', exclusive=True)
name_queue = res.method.queue
print(f"Nome da fila: {name_queue}")
canal.queue_bind(exchange=exc_name, queue=name_queue)
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
