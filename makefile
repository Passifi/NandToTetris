hackASM: main.c assembler.c dynamicArray.c 
	gcc -g main.c assembler.c dynamicArray.c  -o hackASM

test:
	./run_test.sh
