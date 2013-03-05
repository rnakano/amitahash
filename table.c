#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "table.h"
#include "alloc.h"
#include "bucket.h"

#define HASH_AT(x, i) (x[i])

hash_code ah_table_hash(char* key, ulong size)
{
  ulong l = strlen(key);
  return (key[0] * key[l/2] * size) % size;
}

ah_table* ah_table_create(ulong default_size)
{
  ah_table* table = (ah_table*) ah_malloc(sizeof(ah_table));
  ah_bucket** data = (ah_bucket**) ah_malloc(sizeof(ah_bucket*) * default_size);
  /* set data zero-sized buckets list */
  for(ulong i = 0; i < default_size; i++)
  {
    data[i] = ah_bucket_create_empty();
  }
  table->data = data;
  table->current = -1;
  table->size = default_size;
  return table;
}

void ah_table_set(ah_table* table, char* key, char* value)
{
  /* TODO: fix key & value owner */
  hash_code hash = ah_table_hash(key, table->size);
  ah_bucket** bucket = & HASH_AT(table->data, hash);
  ah_bucket_insert(bucket, strdup(key), value);
  /* oh ... strdup ... */
}

char* ah_table_get(ah_table* table, char* key)
{
  hash_code hash = ah_table_hash(key, table->size);
  ah_bucket* bucket = HASH_AT(table->data, hash);
  ah_bucket* find = ah_bucket_search(bucket, key);
  if(find) {
    return find->value;
  } else {
    return NULL;
  }
}

void ah_table_remove(ah_table* table, char* key)
{
  hash_code hash = ah_table_hash(key, table->size);
  ah_bucket** bucket = & HASH_AT(table->data, hash);
  ah_bucket_remove(bucket, key);
}

void ah_table_delete(ah_table* table)
{
  for(uint i = 0; i < table->size; i++)
  {
    ah_bucket_delete(table->data[i]);
    table->data[i] = NULL;
  }
  ah_free(table->data);
  ah_free(table);
}
