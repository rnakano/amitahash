#ifndef _HASH_H_
#define _HASH_H_

#include "type.h"
#include "bucket.h"

typedef struct ah_t_table ah_table;

struct ah_t_table {
  ah_bucket** data;
  ulong current;
  ulong size;
};

typedef uint hash_code;

void* ah_malloc(ulong size);
hash_code ah_table_hash(char* key, ulong size);
ah_table* ah_table_create(ulong default_size);
void ah_table_set(ah_table* table, char* key, char* value);
char* ah_table_get(ah_table* table, char* key);
void ah_table_remove(ah_table* table, char* key);
void ah_table_delete(ah_table* table);

#endif /* _HASH_H_ */
