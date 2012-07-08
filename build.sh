#!/bin/bash
echo "Compiling implementation"
gcc -fPIC -g -c -Wall src/linear_sequence.c -Iheaders

echo "Linking to shared library"
gcc -shared -Wl,-soname,lib_lsq.so.1 \
    -o build/lib_lsq.so.1.0.1 linear_sequence.o  -lc
    
echo "Preparing local library cache"
ldconfig -v -n ./build

echo "Making symbolic link"
ln -sf lib_lsq.so.1 build/lib_lsq.so 

echo "Preparing enviroment"
export LD_LIBRARY_PATH=.:build:$LD_LIBRARY_PATH

gcc -o run_tests tests/lsq_tests.c -Iheaders -L./build  -llib_lsq 
