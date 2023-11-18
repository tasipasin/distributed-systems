#!/usr/bin/env python3

# Formas de utilização:
# Recuperar valor do saldo:
# curl http://localhost:65002/conta
# Depositar valor:
# curl http://localhost:65002/conta -X patch -H "Content-Type:application/json" -d "{\"operation\":\"deposito\", \"value\":INSERIRVALORSEMASPAS}"
# Sacar valor:
# Mesmo comando acima, mas trocar 'deposito' para 'saque'

from flask import Flask
from flask_restful import reqparse, Resource, Api
import re

aplic = Flask(__name__)
api = Api(aplic)
URI = "https://flask-restful.readthedocs.io/en/latest/"

class Conta:
    def __init__(self):
        self.saldo = 0

    def deposito(self, valor):
        self.saldo += valor

    def saque(self, valor):
        self.saldo -= valor

conta = Conta()
parser = reqparse.RequestParser()
parser.add_argument('operation')
parser.add_argument('value')

def executeOperation(op, value):
	resultValue = None
	result = None
	if op == "saque":
		conta.saque(value)
		resultValue = conta.saldo
	elif op == "deposito":
		conta.deposito(value)
		resultValue = conta.saldo
	if resultValue == None:
		errorMessage = {"error": "operation {0} not supported".format(op)}
		result = errorMessage, 400
	else:
		result = {"saldo": resultValue}, 200
	return result

class ContaApi(Resource):
    def get(self):
        return {'saldo' : conta.saldo}, 200

    def patch(self):
        # TODO: Recuperar o conteúdo do corpo
        args = parser.parse_args()
        # Verifica se foi informado tipo de operação
        op = args['operation']
        value = args['value']
        if op == "null":
            result = {"error": "no command received"}, 400
        elif not re.match("^\\d+\\.*\\d*$", value):
            result = {"error" : "value must be a number"}, 400
        else:
            result = executeOperation(op, float(value))
        # Verifica se o tipo da operação é válido
        return result        

api.add_resource(ContaApi, "/conta")


aplic.env = 'development'
aplic.run(port=65002, debug=True)
