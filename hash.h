/*
 * hash.h
 *
 *  Created on: 15 de mar de 2019
 *      Author: alef
 */

#ifndef HASH_H_
#define HASH_H_

typedef struct _element element;

typedef struct _hash_table hash_table;

hash_table* create_hash_table ();

void put (hash_table *ht, int key, int *value);

int *get (hash_table *ht, int key);


#endif /* HASH_H_ */
