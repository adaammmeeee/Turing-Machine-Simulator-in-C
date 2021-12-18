run: compile
	./main

debug: compile
	valgrind --leak-check=full ./main

mt.o: mt.c mt.h
	gcc -Wall -g -c mt.c

main.o: main.c
	gcc -Wall -g -c main.c

calcul_pas.o: calcul_pas.c mt.h
	gcc -Wall -g -c calcul_pas.c

affichage.o : affichage.c mt.h
	gcc -Wall -g -c affichage.c

liste.o: liste.c mt.h
	gcc -Wall -g -c liste.c

reduction.o : reduction.c mt.h
	gcc -Wall -g -c reduction.c

compile: main.o mt.o calcul_pas.o affichage.o liste.o reduction.o
	gcc -Wall -o main main.o mt.o calcul_pas.o affichage.o liste.o reduction.o

clean: 
	rm -f *.o main