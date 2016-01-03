// Table.h

#ifndef _TABLE_H_
#define _TABLE_H_

#include "Extra.h"

typedef struct HashListNode {
  struct HashListNode next;
  char *key;
  char *value;
} HashListNode;

typedef struct HashList {
  HashListNode first;
  HashListNode last;
} HashList;

typedef struct Table {
  HashList *table;
  int size;
} Table;

//Creates table from id.autotable file in current directory, or creates blank table
Table *tableRead(char *id);

//Writes table to id.autotable file in current directory, and destroys table
void tableWrite(Table *t, char *id);

//Returns whether key has an entry (not NULL)
bool tableContains(Table *t, char *key);

//Gets value of corresponding key, or null if nonexistent
char *tableGet(Table *t, char *key);

//Puts (key, value) into table, overwriting existing, copies strings (don't just save pointers), deletes entry if value is null
// Note this function first makes a call to remove to force the overwrite condition
void tablePut(Table *t, char *key, char *value);

//Removes a key value pair from the table. This doesn't require that the key already exist, it simply enforces it being removed
void tableRemove(Table *t, char *key, char *value);

//Frees table, all entries, all strings within entries
void tableDestroy(Table *t);

#endif //_TABLE_H_
