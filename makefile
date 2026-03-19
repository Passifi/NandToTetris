hackASM: main.c assembler.c dynamicArray.h 
	gcc -g main.c assembler.c dynamicArray.h  -o hackASM

test:
	./run_test.sh
