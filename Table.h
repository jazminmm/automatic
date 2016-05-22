// Table.h

#ifndef _TABLE_H_
#define _TABLE_H_

#include "Extra.h"
#include "List.h"

#define INIT_TABLE_SIZE 2

typedef struct HashListNode {
  struct HashListNode *next;
  char *key;
  char *value;
} HashListNode;

typedef struct HashList {
  HashListNode *first;
  HashListNode *last;
} HashList;

typedef struct Table {
  HashList **table;
  int size;
  int maxSize;
  char *id;
} Table;

// Returns size of the table
int tableSize(Table *t);

// Returns maxSize of the table
int tableMaxSize(Table *t);

//Creates table from id.autotable file in current directory, or returns blank Table
Table *tableRead(char *id);

//Writes table to id.autotable file in current directory, and destroys table
void tableWrite(Table *t);

// Returns the pointer to the ID. Becareful to not modify the resulting string!!!
char *tableGetID(Table *t);

// Copies id to the subsequent field in the Table
void tableSetID(Table *t, char *id);

//Returns whether key has an entry (not NULL)
bool tableContains(Table *t, char *key);

//Gets value of corresponding key, or null if nonexistent
char *tableGet(Table *t, char *key);

// Returns 0 if not an integer or the integer in question
int tableGetInt(Table *t, char *key);

// Returns 0.0 if not float or the float in question
float tableGetFloat(Table *t, char *key);

// Returns false unless string is literally "true"
bool tableGetBool(Table *t, char *key);

// Returns a list of Strings which are basically the value tokenized by any character in delimiters or NULL if value is NULL
List *tableGetList(Table *t, char *key, const char *delimiters);

/*
// Returns an array of character pointers or NULL if nothing exists with key. Becarefule to free the resulting char **. You can use the following function have this done for you
char **tableGetStringArray(Table *t, char *key);

// Frees a two dimmension allocated char ** such as the one returned from the previous function.
void freeStringArray(char **sa);
*/

//Puts (key, value) into table, overwriting existing, copies strings (don't just save pointers),
// deletes entry if value is null. Note this function first makes a call
// to tableRemove to force the overwrite condition
void tablePut(Table *t, char *key, char *value);

// adds an entry to t in key, key, with value of every item in l (with delimiter
// concatenated right after each) concatenated onto each other as a massive
// string
void tablePutList(Table *t, char *key, List *l, char *delimiter);

//Removes a key value pair from the table. This doesn't require that the key already exist, it simply enforces it being removed
void tableRemove(Table *t, char *key);

// Clears the table without destroying it
void tableClear(Table *t);

// Frees table, all entries, all strings within entries
void tableDestroy(Table *t);

// creates a HashList and initializes appropriate pointers
HashList *hashListCreate();

// returns number of items that were in the list that was destroyed
int hashListDestroy(HashList *l);

// Appends a new node to teh list with the specified key and value. Returns whether or not size was increased
bool hashListAdd(HashList *l, char *key, char *value);

// returns whether or not something was deleted
bool hashListRemove(HashList *l, char *key);

// returns the value for the given key or NULL if that key doesn't exist
char *hashListFind(HashList *l, char *key);

// Creates a table with the specified size
Table *tableCreate(int size);

// Makes the Table rehashed at double the size of what it was before (also destroys the one given)
void rehash(Table *t);

// Hash Function... Found online
int getHash(char *key, int len);

// Prints all keys in the HashList in format that don't have key[0] == '.'
int hashListPrint(HashList *l, const char *format);

// Prints all keys in the HashList in format
int hashListPrintAll(HashList *l, const char *format);

int hashListDebugPrint(HashList *l, const char *format);

// calls HashListPrint on all existing HashLists in the table
void tablePrint(Table *t, const char *format);

// calls HashListPrintAll on all existing HashLists in the table
void tablePrintAll(Table *t, const char *format);

void tableDebugPrint(Table *t, const char *format);

#endif //_TABLE_H_
