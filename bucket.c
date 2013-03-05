#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"
#include "bucket.h"

ah_bucket* ah_bucket_create_empty()
{
  return NULL;
}

ah_bucket* ah_bucket_create()
{
  ah_bucket* bucket = (ah_bucket*) ah_malloc(sizeof(ah_bucket));
  bucket->next = NULL;
  return bucket;
}

void ah_bucket_insert(ah_bucket** bucket, char* key, char* value)
{
  ah_bucket* ibucket = ah_bucket_create();
  ibucket->key = key;
  ibucket->value = strdup(value);
  if(NULL == *bucket) {
    *bucket = ibucket;
  } else {
    ibucket->next = *bucket;
    *bucket = ibucket;
  }
}

ah_bucket* ah_bucket_search(ah_bucket* bucket, char* key)
{
  if(NULL == bucket) {
    return NULL;
  }
  if(strcmp(bucket->key, key) == 0) {
    return bucket;
  } else {
    return ah_bucket_search(bucket->next, key);
  }
}

uint ah_bucket_length_acc(ah_bucket* bucket, uint acc)
{
  if(NULL == bucket) {
    return acc;
  } else {
    return ah_bucket_length_acc(bucket->next, acc + 1);
  }
}

uint ah_bucket_length(ah_bucket* bucket)
{
  return ah_bucket_length_acc(bucket, 0);
}

void ah_bucket_print(ah_bucket* bucket)
{
  if(NULL == bucket) {
    printf("\n");
    return;
  }
  printf(" %s ", bucket->key);
  ah_bucket_print(bucket->next);
}

void ah_bucket_free(ah_bucket* bucket)
{
  /* ah_free(bucket->key); */
  ah_free(bucket->value);
  ah_free(bucket);
}

void ah_bucket_remove_acc(ah_bucket* bucket, ah_bucket** prev, char* key)
{
  if(NULL == bucket) {
    return;
  }
  if(strcmp(bucket->key, key) == 0) {
    *prev = bucket->next;
    ah_bucket_free(bucket);
    return;
  }
  ah_bucket_remove_acc(bucket->next, &bucket, key);
}

void ah_bucket_remove_i(ah_bucket** bucket, char* key)
{
  if(*bucket != NULL && (*bucket)->next != NULL && strcmp((*bucket)->key, key) == 0) {
    ah_bucket* tmp = *bucket;
    *bucket = tmp->next;
    ah_bucket_free(tmp);
  } else {
    ah_bucket_remove_acc(*bucket, bucket, key);
  }
}

void ah_bucket_remove(ah_bucket** bucket, char* key)
{
  ah_bucket* tgt = *bucket;
  ah_bucket* prev;
  if(NULL == *bucket) return;
  if(strcmp(tgt->key, key) == 0) {
    *bucket = tgt->next;
    ah_bucket_free(tgt);
  } else {
    prev = tgt;
    tgt = tgt->next;
    while(NULL != tgt)
    {
      if(strcmp(tgt->key, key) == 0) {
        prev->next = tgt->next;
        ah_bucket_free(tgt);
        return;
      }
      prev = tgt;
      tgt = tgt->next;      
    }
  }
}

void ah_bucket_delete(ah_bucket* bucket)
{
  if(bucket == NULL) return;
  ah_bucket* next = bucket->next;
  ah_bucket_free(bucket);
  ah_bucket_delete(next);
}
