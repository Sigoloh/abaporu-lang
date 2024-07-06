# /bin/bash

echo 'Compilando o compilador'

g++ ./main.cpp -o main

echo './examples/SimpleHelloWorld.abapl'
echo 'stdout: '
main -i ./examples/SimpleHelloWorld.abapl
echo ''

echo './examples/BlockHelloWorld.abapl'
echo 'stdout: '
main -i ./examples/BlockHelloWorld.abapl
echo ''

echo './examples/LoopsHelloWorld.abapl'
echo 'stdout: '
main -i ./examples/LoopsHelloWorld.abapl
echo ''

echo './examples/BlocksAndLoops.abapl'
echo 'stdout: '
main -i ./examples/BlocksAndLoops.abapl


