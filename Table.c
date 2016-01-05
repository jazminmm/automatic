#include "Table.h"

Table *tableRead(char *id) {
  Table *t;
  char temp[501] = {};
  sprintf(temp, "%s.autotable", id);
  FILE *fp = fopen(temp, "r");
  if (fp) {
    t = tableCreate(INIT_TABLE_SIZE); // we start with a size of 2
    while(fgets(temp, 500, fp)) {
      char key[101] = {};
      char value[401] = {};
      sscanf(temp, "%s: %s", key, value);


      /*int i;
        for (i = 0; temp[i] != ':'; i++) {
        key[i] = temp[i];
        }
        int j = 0;
        for (i += 2; temp[i] != '\n' && temp[i] != '\0'; i++) {
        value[j++] = temp[i];
        }
        */
      tablePut(t, key, value);
    }
    fclose(fp);
  } else if (true) {
    printf("%s.autotable doesn't exist when calling tableRead()\n", id);
    exit(1);
  }
  return t;
}

void tableWrite(Table *t, char *id) {
  if (!t) {
    printf("NULL Table passed to tableWrite()\n");
    exit(1);
  }
  int count = 0;
  char temp[501] = {};
  sprintf(temp, "%s.autotable", id);
  FILE *fp = fopen(temp, "r");
  for (int i = 0; i < t->size; i++) {
    if (!t->table[i]) continue;
    for (HashListNode *tempn = t->table[i]->first; tempn; tempn = tempn->next) {
      fprintf(fp, "%s: %s", tempn->key, tempn->value);
      count++;
    }
    if (count == t->size) break;
  }
  fclose(fp);
  tableDestroy(t);
}

bool tableContains(Table *t, char *key) {
  if (!t) {
    printf("NULL Table passed to tableContains()\n");
    exit(1);
  }
  int hash = getHash(key, t->size);
  if (t->table[hash] && hashListFind(t->table[hash], key))
    return true;
  return false;
}

char *tableGet(Table *t, char *key) {
  if (!t) {
    printf("NULL HashTable pased to tableGet()\n");
    exit(1);
  }
  int hash = getHash(key, t->size);
  if (!t->table[hash]) return NULL;
  return hashListFind(t->table[hash], key);
  /*for (HashListNode temp = t->table[hash]->first; temp; temp = temp->next) {
    if (!strcmp(temp->key, key)) return temp->value;
  }*/
  return NULL;
}

void tablePut(Table *t, char *key, char *value) {
  if (!t) {
    printf("NULL HashTable passed to tablePut()\n");
    exit(1);
  }
  int hash = getHash(key, t->size);
  if (!t->table[hash]) {
    t->table[hash] = hashListCreate();
  }
  if (hashListAdd(t->table[hash], key, value)) t->size++;
}

void tableRemove(Table *t, char *key) {
  if (!t) {
    printf("Passed NULL Table to tableRemove()\n");
    exit(1);
  }
  int hash = getHash(key, t->size);
  if (!t->table[hash]) return;
  hashListRemove(t->table[hash], key);
}

void tableDestroy(Table *t) {
  int count = 0;
  for (int i = 0; i < t->size; i++) {
    if (!t->table[i]) continue;
    count += hashListDestroy(t->table[i]);
    if (count == t->size) break;
  }
  free(t->table);
  free(t);
}

HashList *hashListCreate() {
  HashList *l = malloc(sizeof(HashList));
  l->first = NULL;
  l->last = NULL;
  return l;
}

// returns number of items that were originally in the list
int hashListDestroy(HashList *l) {
  if (!l) {
    printf("NULL HashList passed to hashListDestroy()\n");
    exit(1);
  }
  int count = 0;
  if (!l->first) return count;
  if (!l->first->next) {
    hashListRemove(l, l->first->key);
    return ++count;
  }
  HashListNode *temp = l->first;
  HashListNode *temp2 = l->first->next;
  while (temp2) {
    hashListRemove(l, temp->key);
    temp = temp2;
    temp2 = temp2->next;
    count++;
  }
  hashListRemove(l, temp->key);
  return ++count;
}

// currently always appends and returns true when size should increase
bool hashListAdd(HashList *l, char *key, char *value) {
  if (!l) {
    printf("NULL HashList passed to hashListAdd()\n");
    exit(1);
  }
  bool incsize = !hashListRemove(l, key);
  HashListNode *temp = malloc(sizeof(HashListNode));
  temp->key = calloc(101, sizeof(char));
  sprintf(temp->key, "%s", key);
  temp->value = calloc(401, sizeof(char));
  sprintf(temp->value, "%s", value);
  if (!l->first || !l->last) {
    l->first = malloc(sizeof(HashListNode));
    l->last = l->first;
  } else {
    l->last->next = malloc(sizeof(HashListNode));
    l->last = l->last->next;
  }
  l->last->next = NULL;
  return incsize;
}

// returns whether or not something was actually removed
bool hashListRemove(HashList *l, char *key) {
  if (!l) {
    printf("NULL HashList passed to hashListRemove()\n");
    exit(1);
  }
  if (!l->first || !l->last) return false;
  if (!l->first->next) {
    if (!strcmp(l->first->key, key)) {
      free(l->first->key);
      free(l->first->value);
      free(l->first);
      l->first = NULL;
      l->last = NULL;
      return true;
    }
    return false;
  }
  if (!strcmp(l->first->key, key)) {
    HashListNode *temp = l->first;
    l->first = l->first->next;
    free(temp->key);
    free(temp->value);
    free(temp);
    return true;
  }
  HashListNode *p = l->first;
  HashListNode *c = p->next;
  while(c) {
    if (!strcmp(c->key, key)) break;
    p = c;
    c = c->next;
  }
  if (!c) return false;
  if (c == l->last) l->last = p;
  p->next = c->next;
  free(c->key);
  free(c->value);
  free(c);
  return true;
}

char *hashListFind(HashList *l, char *key) {
  if (!l) {
    printf("NULL HashList passed to hashListFind()\n");
    exit(1);
  }
  for (HashListNode *temp = l->first; temp; temp = temp->next)
    if (!strcmp(key, temp->key))
      return temp->value;
  return NULL;
}

Table *tableCreate(int size) {
  Table *t = malloc(sizeof(Table));
  t->table = calloc(size, sizeof(HashList *));
  t->size = 0;
  return t;
}

Table *rehash(Table *t) {
  if (!t) {
    printf("NULL HashTable passed to rehash()\n");
    exit(1);
  }

 // Table n = tableCreate();
  return NULL;
}

int getHash(char *key, int len) {
  unsigned int hash;
  unsigned int  i;
  for (hash=0, i=0; i < strlen(key); ++i) hash=hash^key[i];
  return ((hash)%len);
}

