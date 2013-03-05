#include "table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 2000
#define KEYS 1000
#define KEY_LEN 20

char data[KEYS][KEY_LEN];

void gen_random_key(char* dst, uint k, uint len)
{
  char buff[len];
  uint i;
  for(i = 0; i < len-8; i++) {
    char c = (rand() % 26) + 97;
    buff[i] = c;
  }
  buff[i] = '\0';
  sprintf(dst, "%s%d", buff, k);
}

int main(int argc, char *argv[])
{
  ah_table* table = ah_table_create(TABLE_SIZE);
  char keybuff[KEY_LEN], valuebuff[100];

  /* insert */
  for(uint i = 0; i < KEYS; i++) {
    uint len = rand() % (KEY_LEN - 8) + 8;
    gen_random_key(keybuff, i, len);
    sprintf(valuebuff, "%d", i);
    strcpy(data[i], keybuff);
    ah_table_set(table, keybuff, valuebuff);
  }

  /* lookup */
  for(uint k = 0; k < 10; k++) {
    for(uint i = 0; i < KEYS; i++) {
      char* value = ah_table_get(table, data[i]);
      if(atoi(value) != i) {
        printf("value is changed!!\n");
        break;
      }
    }
  }

  /* puts("ready to delete..."); */
  /* getchar(); */
  /* /\* delete *\/ */
  /* for(uint i = 0; i < KEYS; i++) { */
  /*   ah_table_remove(table, data[i]); */
  /* } */
  /* puts("delete"); */
  /* getchar(); */

  ah_table_delete(table);

  return 0;
}

