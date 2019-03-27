#CC=cc
#CXX=CC
#CCFLAGS= -g -std=c99 -Wall -Werror

all: treeh test
	
treeh: main.o compress.o extract.o structs.o 
	gcc main.o compress.o extract.o structs.o -lm -o treeh

compress.o: compress.c compress.h 
	gcc -c compress.c

main.o: main.c compress.h extract.h structs.h tad.h
	gcc -c main.c
	
extract.o: extract.c extract.h
	gcc -c extract.c
	

structs.o: structs.c structs.h
	gcc -c structs.c

test: treeh
	./treeh

clean:
	rm -f *.o compress main extract structs output.txt treeh