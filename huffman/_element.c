/*
 * _element.c
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 256

typedef struct _element {
  int size;
  unsigned char way[HASH_SIZE];
} element;
