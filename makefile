run: compile
	./main

debug: compile
	valgrind --leak-check=full ./main

mt.o: mt.c mt.h
	gcc -Wall -g -c mt.c

main.o: main.c
	gcc -Wall -g -c main.c

fonctionnement.o: fonctionnement.c mt.h
	gcc -Wall -g -c fonctionnement.c

affichage.o : affichage.c mt.h
	gcc -Wall -g -c affichage.c

liste.o: liste.c mt.h
	gcc -Wall -g -c liste.c

reduction.o : reduction.c mt.h
	gcc -Wall -g -c reduction.c

compile: main.o mt.o fonctionnement.o affichage.o liste.o reduction.o
	gcc -Wall -o main main.o mt.o fonctionnement.o affichage.o liste.o reduction.o

clean: 
	rm -f *.o main