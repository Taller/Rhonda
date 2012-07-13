#!/bin/bash

rm build/*.*
echo "Compiling implementation"
gcc -fPIC -c -o build/liblsq.o src/linear_sequence.c -Iinclude
ld -shared -soname liblsq.so.1 -o ./build/liblsq.so.1.0 -lc ./build/liblsq.o

echo "Preparing local library cache"
ldconfig -v -n ./build

echo "Making symbolic link"
ln -sf liblsq.so.1 ./build/liblsq.so 

echo "Preparing enviroment"
export LD_LIBRARY_PATH=.:./build:$LD_LIBRARY_PATH

echo "Compiling tests"
gcc -c -o build/lsq_tests.o tests/lsq_tests.c -I include 

echo "Linking tests"
gcc  -o run_tests -I include -L./build -llsq build/lsq_tests.o

./run_tests