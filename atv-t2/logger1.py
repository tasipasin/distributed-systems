#!/usr/bin/python3

from pika import BlockingConnection

exc_name = 'newExc'

def callback(ch, method, properties, body):
    print(body.decode())

conexao = BlockingConnection()
canal = conexao.channel()
canal.exchange_declare(exchange=exc_name, exchange_type='topic')
res = canal.queue_declare(queue='', exclusive=True)
name_queue = res.method.queue
print("Apenas eventos críticos")
print(f"Nome da fila: {name_queue}")
canal.queue_bind(exchange=exc_name, queue=name_queue, routing_key="log.*.critical")
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
