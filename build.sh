#!/bin/bash
echo "Compiling implementation"
gcc -fPIC -c -o build/liblsq.o src/linear_sequence.c -Iheaders
ld -shared -soname liblsq.so.1 -o ./build/liblsq.so.1.0 -lc ./build/liblsq.o
#gcc -fPIC -g -c -Wall src/linear_sequence.c -Iheaders

#echo "Linking to shared library"
#gcc -shared -Wl,-soname,lib_lsq.so.1 \
#    -o build/lib_lsq.so.1.0.1 linear_sequence.o  -lc
    
echo "Preparing local library cache"
ldconfig -v -n ./build

echo "Making symbolic link"
ln -sf liblsq.so.1 ./build/liblsq.so 

echo "Preparing enviroment"
export LD_LIBRARY_PATH=.build/:$LD_LIBRARY_PATH

gcc -o run_tests tests/lsq_tests.c -Iheaders -L./build -lliblsq
