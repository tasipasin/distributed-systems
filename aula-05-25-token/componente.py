#!/usr/bin/env python3

# SDC
# Prof. Luiz Lima Jr.

from pika import BlockingConnection
from sys import argv

if len(argv) < 2:
    print(f'Uso: {argv[0]} <id> <v1> [<v2> ...]')
    exit(1)

idx = argv[1]       # identificador da entidade
Nx = argv[2:]       # vizinhos do componente
old_msg = ""

conexao = BlockingConnection()
canal = conexao.channel()

canal.queue_declare(queue=idx, auto_delete=True)
for v in Nx:
    canal.queue_declare(queue=v, auto_delete=True)

def envia(msg, dests):
    msg = f'{idx}:{msg}'   # ORIGEM:MSG
    for d in dests:
        canal.basic_publish(exchange='',
                            routing_key=d,
                            body=msg)

def recebendo(msg, origem):
    global old_msg
    # aqui a logica do algoritmo distribuido
    print(f'"{msg}" recebido de {origem}')
    if msg != old_msg:
        vz = Nx[:]
        if origem in vz : vz.remove(origem)
        envia(msg, vz)
        old_msg = msg

def espontaneamente(msg):
    # mensagem recebida do starter
    print(f'"{msg}" recebido do STARTER')
    envia(msg, Nx)

def trata_msg(canal, metodo, props, corpo):
    m = corpo.decode().split(':')
    if len(m)<2:
        origem = "NULL"
        msg = m[0]
    else:
        origem = m[0]
        msg = m[1]
    if origem == 'STARTER':
        espontaneamente(msg)
    else:
        recebendo(msg, origem)

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
