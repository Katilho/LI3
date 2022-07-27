all: guiao-3 tests

guiao-3: ./obj/guiao-3.o
	gcc -Wall -g ./obj/auxFunctions.o ./obj/user.o ./obj/users.o ./obj/commit.o ./obj/commits.o ./obj/repo.o ./obj/repos.o ./obj/parsing.o ./obj/stats.o ./obj/tuple.o ./obj/query.o ./obj/printer.o ./obj/guiao-3.o -o guiao-3

./obj/guiao-3.o: ./src/guiao-3.c
	gcc -Wall -g -c ./src/auxFunctions.c ./src/user.c ./src/users.c ./src/commit.c ./src/commits.c ./src/repo.c ./src/repos.c ./src/parsing.c ./src/stats.c ./src/tuple.c ./src/query.c ./src/printer.c ./src/guiao-3.c
	mv auxFunctions.o user.o users.o commit.o commits.o repo.o repos.o parsing.o stats.o tuple.o query.o printer.o guiao-3.o ./obj


tests: ./obj/tests.o
	gcc -Wall -g ./obj/auxFunctions.o ./obj/user.o ./obj/users.o ./obj/commit.o ./obj/commits.o ./obj/repo.o ./obj/repos.o ./obj/parsing.o ./obj/stats.o ./obj/tuple.o ./obj/query.o ./obj/timetests.o ./obj/functionaltests.o ./obj/tests.o -o tests

./obj/tests.o: ./src/tests.c
	gcc -Wall -g -c ./src/auxFunctions.c ./src/user.c ./src/users.c ./src/commit.c ./src/commits.c ./src/repo.c ./src/repos.c ./src/parsing.c ./src/stats.c ./src/tuple.c ./src/query.c ./src/timetests.c ./src/functionaltests.c ./src/tests.c
	mv auxFunctions.o user.o users.o commit.o commits.o repo.o repos.o parsing.o stats.o tuple.o query.o timetests.o functionaltests.o tests.o ./obj


menu:
	./guiao-3

query:
	./guiao-3 commands.txt

test:
	./tests testcommands.txt

clean:
	rm ./obj/*.o ./saida/*.txt ./saida/*.csv ./tmp/*.txt guiao-3 tests