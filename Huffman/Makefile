#CC=cc
#CXX=CC
#CCFLAGS= -g -std=c99 -Wall -Werror

all: treeh test
	
treeh: Huffman.o compress.o extract.o tree.o queue.o hash.o 
	gcc Huffman.o compress.o extract.o tree.o queue.o hash.o -lm -o treeh

compress.o: compress.c compress.h 
	gcc -c compress.c

main.o: Huffman.c compress.h extract.h tree.h queue.h hash.h
	gcc -c Huffman.c
	
extract.o: extract.c extract.h compress.h
	gcc -c extract.c
	
tree.o: tree.c tree.h
	gcc -c tree.c
	
queue.o: queue.c queue.h
	gcc -c queue.c
	
hash.o: hash.c hash.h
	gcc -c hash.c

test: treeh
	./treeh

clean:
	rm -f *.o compress Huffman extract tree queue hash output.txt treeh