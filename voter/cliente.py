#!/usr/bin/python3

import Pyro5.api as pyro
import Pyro5.errors as errors
from sys import argv

try:
    voterName = argv[1]
    voter = pyro.Proxy("PYRONAME:"+voterName)
    end = False
    while not end:
        toSend = input()
        end = toSend == "sair"
        if not end:
            voter.send(toSend)

except errors.CommunicationError as error:
    print("Unavailable...")
    print(f"Error: {error}")

