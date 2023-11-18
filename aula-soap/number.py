#!/usr/bin/env python3

from zeep import Client

ZEEP_URL = "https://www.dataaccess.com/webservicesserver/NumberConversion.wso"
INTERFACE = "?wsdl"

print(ZEEP_URL + INTERFACE)
client = Client(ZEEP_URL + INTERFACE)
run = True
while(run):
    print()
    entry = int(input("Insira um número\n"))
    if entry >= 0:
        print(client.service.NumberToWords(int(entry)))
    else:
        run = False
    
