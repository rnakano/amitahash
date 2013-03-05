#include <stdlib.h>
#include <stdio.h>
#include "type.h"

void* ah_malloc(ulong size)
{
  void* ptr = malloc(size);
  if(!ptr){
    fprintf(stderr, "Memory allocation error.\n");
    exit(1);
  }
  return ptr;
}

void ah_free(void* ptr)
{
  if(ptr) {
    free(ptr);
  }
}
