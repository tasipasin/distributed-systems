#!/usr/bin/env python3

from requests import get
import sys

API_URL='http://api.openweathermap.org/data/2.5/weather?q=Curitiba,BR&appid=442de31b43491aba83051131ecfeffe3'
CITY = None

def getApiUrl():
    global API_URL
    return API_URL

def getCity():
    global CITY
    return CITY

def setCity(value):
    global CITY
    CITY = value

def getParameter():
    args = sys.argv
    if len(args) > 1:
        setCity(args[1])
    else:
        print("Informe um parâmetro")

def main():
    #getParameter()
    resp = get(getApiUrl())
    jason = resp.json()
    print("Mensage recebida")
    tempC = round(float(jason["main"]["temp"] - 273.15), 2)
    print(tempC)

if __name__ == '__main__':
    main()
