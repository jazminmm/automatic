#include "Table.h"

Table *tableRead(char *id) {
  Table *t = tableCreate();
  if (false) {

  }
  return t;
}

void tableWrite(Table *t, char *id) {
  //write to id.autotable
  if (!t) {
    printf("NULL Table passed to tableWrite()\n");
    exit(1);
  }
  tableDestroy(t);
}

bool tableContains(Table *t. char *key) {
  if (!t) {
    printf("NULL Table passed to tableContains()\n");
    exit(1);
  }
  int hash = hash(key, t->size);
  if (t->table[hash] && hashListFind(t->table[hash], key))
    return true;
  return false;
}

char *tableGet(Table *t, char *key) {

}

HashList *hashListCreate() {
  HashList *l = malloc(sizeof(HashList));
  l->first = NULL;
  l->last = NULL;
  return l;
}

void hashListAdd(HashList *l, char *key, char *value) {

}

// returns whether or not something was actually removed
bool hashListRemove(HashList *l, char *key) {
  if (!l) {
    printf("NULL HashList passed to hashListRemove()\n");
    exit(1);
  }
  if (!l->first) return;
  if (!l->first->next) {
    if (!strcmp(l->first->key, key)) {
      free(l->first);
      l->first = NULL;
      l->last = NULL;
    }
    return;
  }
  HashListNode *c = l->first;
  HashListNode *p = c->next;
  // continue please
}

char *hashListFind(HashList *l, char *key) {
  if (!l) {
    printf("NULL HashList passed to hashListFind()\n");
    exit(1);
  }
  for (HashListNode *temp = l->first; temp; temp = temp->next)
    if (!strcmp(key, temp->key))
      return temp;
  return NULL;
}

Table *tableCreate() {
  Table *t = malloc(sizeof(Table));
  t->table = calloc(2, sizeof(HashList));
  t->size = 0;
  return t;
}

void rehash() {
}

int hash(char *key, int len) {
  int hash;
  int  i;
  for (hash=0, i=0; i < strlen(key); ++i) hash=hash^key[i];
  return ((hash%101)%len);         /* 101 is prime */
}


