#!/usr/bin/python3

import Pyro5.api as pyro
from sys import argv
import math
import signal

# vid = identificador do Voter
# ve = número de mensagens esperadas
# to = timeout
# vr = número de mensagens recebidas

if len(argv) < 4:
    print("\nInvalid")
    print("Use: servidor.py <id> <ve> <timeout>\n")
    exit(1)

myId = argv[1]
ve = int(argv[2])
timeout = int(argv[3])

@pyro.expose
class Voter:
    def __init__(self, myId, ve):
        self.id = myId
        self.recebidas = {}
        self.receivedAmount = 0
        # Quantidades esperadas 
        self.ve = ve
        

    def send(self, mensagem):
        if self.receivedAmount == 0:
            startTimeout()
        print(f"Mensagem recebida {mensagem}")    
        # Incrementa se já recebeu uma mensagem igual
        if mensagem in self.recebidas:
            self.recebidas[mensagem] += 1
        # Inicializa se é a primeira vez que recebe a mensagem
        else:
            self.recebidas[mensagem] = 1
        self.receivedAmount += 1
        self.getWinner(False)
    
    def getWinner(self, timeoutHit):
        receivedMajority = math.ceil((self.receivedAmount + 1) / 2)
        # Verifica se recebeu a quantidade de mensagens antes do timeout
        if timeoutHit or self.receivedAmount == self.ve:
            ganhador = None
            for msg in self.recebidas:
                # Verifica se o ganhador ainda nao foi determinado
                # ou se o contador da mensagem for maior que a maioria recebida
                # e se maior que a do ganhador ja determinada
                if self.recebidas[msg] >= receivedMajority and (ganhador == None or self.recebidas[msg] > self.recebidas[ganhador]):
                    ganhador = msg
            print(f"-> Ganhador: {ganhador}\n")
            self.resetReceivedList()

    def resetReceivedList(self):
        resetTimeout()
        self.recebidas.clear()
        self.receivedAmount = 0

voter = Voter(myId, ve)

def startTimeout():
    signal.alarm(timeout)
    print(f"Timeout inicializado com {timeout} segundos")

def resetTimeout():
    signal.alarm(0)
    print("Timeout zerado")
    
def alarm_handler(nsinal, pilha):
    voter.getWinner(True)
    
signal.signal(signal.SIGALRM, alarm_handler)

# Server & IOR
daemon = pyro.Daemon()
uri = daemon.register(voter)

# Name server
nameServer = pyro.locate_ns()
nameServer.register(myId, uri)

print("Aguardando mensagens...")
daemon.requestLoop()
