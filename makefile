run: compile
	./main 1

test: compile
	./main 2

test1: compile
	./main 3

test2: compile
	valgrind --leak-check=full ./main 4

debug: compile
	valgrind --leak-check=full ./main 1

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

reduction_infini.o : reduction_infini.c mt.h
	gcc -Wall -g -c reduction_infini.c

reduction_abcd.o : reduction_abcd.c mt.h
	gcc -Wall -g -c reduction_abcd.c

optimisation.o : optimisation.c mt.h
	gcc -Wall -g -c optimisation.c


compile: main.o mt.o calcul_pas.o affichage.o liste.o reduction_infini.o reduction_abcd.o optimisation.o
	gcc -Wall -o main *.o

clean: 
	rm -f *.o *_Vbinaire *_VsemiInfini main