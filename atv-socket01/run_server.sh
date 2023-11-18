#!/bin/sh

FILE=servidor_eco.cpp
PORTA=$1
clang++ $FILE -o toRun_server
toRun_server $PORTA
rm toRun
