#ifndef _BUCKET_H_
#define _BUCKET_H_

#include "type.h"

typedef struct ah_t_bucket ah_bucket;

struct ah_t_bucket {
  char* key;
  char* value;
  ah_bucket* next;
};

ah_bucket* ah_bucket_create();
void ah_bucket_insert(ah_bucket** bucket, char* key, char* value);
ah_bucket* ah_bucket_search(ah_bucket* bucket, char* key);
void ah_bucket_print(ah_bucket* bucket);
ah_bucket* ah_bucket_create_empty();
uint ah_bucket_length(ah_bucket* bucket);
void ah_bucket_remove(ah_bucket** bucket, char* key);
void ah_bucket_delete(ah_bucket* bucket);

#endif /* _BUCKET_H_ */
