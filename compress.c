/*
 * compress.c
 *
 *  Created on: 15 de mar de 2019
 *      Author: alef
 */

#include <stdio.h>
#include <stdlib.h>

#include "compress.h"
#include "extract.h"
#include "queue.h"
#include "tree.h"
#include "hash.h"

typedef struct _node
{
	char item;
	int priority;
	struct _node *next, *left, *right;
} node;

typedef struct _priority_queue
{
	node *head;
} priority_queue;

#define MAX 100

int is_bit_i_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask & c;
}

unsigned char set_bit(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask | c;
}

void print_byte(FILE *file, int array) {
	int cont, caracter;
	for(cont = 7; cont >= 0; cont--) {
		set_bit(caracter, cont);
		if(cont == 0) {
			fputc(caracter, file);
			cont = 7;
			caracter = 0;
		}
	}
}

void compress(FILE *file, FILE *compress_file, node *root, int file_size) {
	int array[MAX];
	fputc(0, compress_file);
	fputc(0, compress_file);
	unsigned char caracter;
	print_pre_order(root, compress_file);
	while(caracter != EOF){

	}
}
