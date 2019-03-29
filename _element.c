/*
 * _element.c
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_HASH 256

typedef struct _element {
  int size;
  unsigned char way[HASH_SIZE];
} element;
