all: compile run

compile:
	gcc -I ./include/ -o ./lib/jrb.o -c ./src/jrb.c
	gcc -I ./include/ -o ./lib/fields.o -c ./src/fields.c
	gcc -I ./include/ -o ./lib/jval.o -c ./src/jval.c
	gcc -I ./include/ -o ./bin/deneme ./lib/jrb.o ./lib/fields.o ./lib/jval.o ./src/deneme.c

run:
	./bin/deneme
