#CC=cc
#CXX=CC
#CCFLAGS= -g -std=c99 -Wall -Werror

all: huffman test

huffman: main.o _compress.o _extract.o _hash_table.o _element.o _priority_queue.o _node.o _binary_tree.o
	gcc main.o _compress.o _extract.o _hash_table.o _element.o _priority_queue.o _node.o _binary_tree.o  -lm -o huffman

main.o : main.c _compress.h _extract.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

_compress.o :_compress.c _compress.h _hash_table.h _priority_queue.h
	gcc -o _compress.o _compress.c -c -W -Wall -ansi -pedantic

_hash_table.o : _hash_table.c _hash_table.h _element.h
	gcc -o _hash_table.o _hash_table.c -c -W -Wall -ansi -pedantic

_element.o : _element.c _element.h
	gcc -o _element.o _element.c -c -W -Wall -ansi -pedantic

_priority_queue.o : _priority_queue.c _priority_queue.h  _node.h
	gcc -o _priority_queue.o _priority_queue.c

_node.o : _node.c _node.h
	gcc -o _node.o _node.c -c -W -Wall -ansi -pedantic

_extract.o :  _extract.c _extract.h _binary_tree.h
	gcc -o _extract.o _extract.c -c -W -Wall -ansi -pedantic

_binary_tree.o : _binary_tree.c _binary_tree.h
	gcc -o _binary_tree.o _binary_tree.c

test: huffman
	./huffman

clean:
	rm -rf *.o *~ huffman



