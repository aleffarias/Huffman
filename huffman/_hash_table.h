/*
 * _hash_table.h
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

typedef struct _hash_table hash_table;

hash_table *create_hash_table();

void put(hash_table *ht, int key, int size, unsigned char *way);

void save_way(hash_table *ht, node *tree, unsigned char *way, int pos);

#endif /* HASH_TABLE_H_ */
