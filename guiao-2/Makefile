all: guiao-2

guiao-2: ./obj/guiao-2.o
	gcc -Wall -g ./obj/user.o ./obj/users.o ./obj/commit.o ./obj/commits.o ./obj/repo.o ./obj/repos.o ./obj/parsing.o ./obj/stats.o ./obj/tuple.o ./obj/query.o ./obj/guiao-2.o -o guiao-2

./obj/guiao-2.o: ./src/guiao-2.c
	gcc -Wall -g -c ./src/user.c ./src/users.c ./src/commit.c ./src/commits.c ./src/repo.c ./src/repos.c ./src/parsing.c ./src/stats.c ./src/tuple.c ./src/query.c ./src/guiao-2.c
	mv user.o users.o commit.o commits.o repo.o repos.o parsing.o stats.o tuple.o query.o guiao-2.o ./obj

test:
	./guiao-2 commands.txt

clean:
	rm ./obj/*.o ./saida/*.txt guiao-2