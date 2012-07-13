all:
	@cc -fPIC -c -o build/liblsq.o src/linear_sequence.c -I include
	@ld -shared -soname liblsq.so.1 -o ./build/liblsq.so.1.0 -lc ./build/liblsq.o
	@ldconfig -n ./build
	@ln -sf liblsq.so.1 ./build/liblsq.so 
	@gcc -c -o build/lsq_tests.o tests/lsq_tests.c -I include
	@gcc -o run_tests -I include -L./build -llsq build/lsq_tests.o
	@LD_LIBRARY_PATH=.:./build:D_LIBRARY_PATH ./run_tests