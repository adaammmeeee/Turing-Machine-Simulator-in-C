run: compile
	./main

debug: compile
	valgrind --leak-check=full ./main

mt.o: mt.c mt.h
	gcc -Wall -g -c mt.c

main.o: main.c
	gcc -Wall -g -c main.c

compile: main.o mt.o
	gcc -Wall -o main main.o mt.o