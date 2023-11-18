#!/usr/bin/env python3

from flask import Flask
from flask_restful import Resource, Api

aplic = Flask(__name__)
api = Api(aplic)
URI = "https://flask-restful.readthedocs.io/en/latest/"

class Eco:
    def __init__(self):
        self.sufixo = "_ECO"
        self.cont = 0

    def diga(self, msg):
        self.cont += 1
        return msg + self.sufixo

eco = Eco()

class EcoApi(Resource):
    def get(sel):
        return {'contador' : eco.cont}

    def patch(self, msg):
        return {'resp' : eco.diga(msg)}

api.add_resource(EcoApi, "/eco", "/eco/<string:msg>")

aplic.env = 'development'
aplic.run(port=65001, debug=True)
