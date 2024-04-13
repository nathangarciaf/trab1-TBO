all:
	gcc -Wall -g -o trab1 *.c -lm

valgrind:
	valgrind --track-origins=yes --leak-check=full ./trab1 entrada.txt 2 saida.txt
