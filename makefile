all:
	gcc -Wall -g -o trab1 *.c -lm

valgrind_test:
	valgrind --track-origins=yes --leak-check=full ./trab1 entrada.txt 3 saida.txt
