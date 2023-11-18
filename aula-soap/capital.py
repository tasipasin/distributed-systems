#!/usr/bin/env python3

from zeep import Client

ZEEP_URL = "http://webservices.oorsprong.org/websamples.countryinfo/CountryInfoService.wso"
INTERFACE = "?wsdl"

print(ZEEP_URL + INTERFACE)
client = Client(ZEEP_URL + INTERFACE)
run = True
while(run):
    print()
    entry = input("Digite a sigla de um país, em inglês\n")
    entry = entry.upper()
    if entry != "EXIT":
        print(client.service.CapitalCity(entry))
    else:
        run = False
    
