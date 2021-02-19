#!/bin/sh

# create bin dir if not exists
mkdir -p bin

# creating object file for the main part
gcc -c  -o bin/mainlib.o mainlib.c
# creating object file for the library
gcc -c -fPIC -o bin/dynlib.o  dynlib.c
# creating dynamic library itself
gcc -o bin/dynlib.so -shared bin/dynlib.o 
# creating an executable and linking it with the dynamic library
gcc -o bin/main  bin/mainlib.o bin/dynlib.so


# libraries are searched for in /lib/
# so loader will find it there or
# another path must be provided using
# enviroment variables (valid in this
# shell session):
export LD_LIBRARY_PATH=./bin

# find dll of executable:
echo "Print all dll's required by ./bin/main executable:"
ldd ./bin/main

# run
echo "Running ./bin/main"
./bin/main
