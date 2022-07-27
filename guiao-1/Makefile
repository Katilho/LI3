all: guiao-1

guiao-1: ./obj/guiao-1.o
	gcc -Wall -g ./obj/guiao-1.o -o guiao-1

./obj/guiao-1.o: ./src/guiao-1.c
	gcc -Wall -g -c ./src/guiao-1.c
	mv guiao-1.o ./obj

e1:
	./guiao-1 exercicio-1

e2:
	./guiao-1 exercicio-2

clean:
	rm ./obj/*.o ./saida/*.csv guiao-1