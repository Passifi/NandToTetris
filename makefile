hackASM: main.c assembler.c dynamicArray.c parser.c 
	gcc -g main.c assembler.c dynamicArray.c parser.c  -o hackASM

test:
	./run_test.sh
