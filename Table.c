#include "Table.h"

int tableSize(Table *t) {
  if(!t) {
    printf("Passed NULL Table to tableSize()\n");
    exit(1);
  }
  return t->size;
}

int tableMaxSize(Table *t) {
  if(!t) {
    printf("Passed NULL Table to tableMaxSize()\n");
    exit(1);
  }
  return t->maxSize;
}

Table *tableRead(char *id) {
  Table *t;
  char temp[501] = {};
  sprintf(temp, "%s.autotable", id);
  debugPrint("TABLE reading from <%s>", temp);
  t = tableCreate(INIT_TABLE_SIZE); // we start with a size of 2
  tableSetID(t, id);
  FILE *fp = fopen(temp, "r");
  if(fp) {
    while(fgets(temp, 500, fp)) {
      char key[101] = {};
      char value[401] = {};
      sscanf(temp, "%s: %s", key, value);
      tablePut(t, key, value);
    }
    fclose(fp);
  }
  return t;
}

void tableWrite(Table *t) {
  if(!t) {
    autoError("NULL Table passed to tableWrite()");
  }
  if(streq(tableGetID(t), "")) autoError("Table with no ID passed to tableWrite()");
  int count = 0;
  char temp[501] = {};
  sprintf(temp, "%s.autotable", tableGetID(t));
  FILE *fp = fopen(temp, "r");
  if(fp) { // Force deletion of file
    fclose(fp);
    unlink(temp); // file delete function
  }
  if(tableSize(t) == 0) return; // We force delete the filewhen the table is empty
  debugPrint("TABLE writing to <%s>", temp);
  fp = fopen(temp, "w");
  for (int i = 0; i < t->size; i++) {
    if(!t->table[i]) continue;
    for (HashListNode *tempn = t->table[i]->first; tempn; tempn = tempn->next) {
      debugPrint("  %s: %s", tempn->key, tempn->value);
      fprintf(fp, "%s: %s\n", tempn->key, tempn->value);
      count++;
    }
    if(count == t->size) break;
  }
  fclose(fp);
  tableDestroy(t);
}

char *tableGetID(Table *t) {
  if(!t) autoError("Passed NULL Table to tableSize()");
  return t->id;
}

void tableSetID(Table *t, char *id) {
  if(!t) autoError("Passed NULL Table to tableSize()");
  sprintf(t->id, "%s", id);
}

bool tableContains(Table *t, char *key) {
  if(!t) autoError("NULL Table passed to tableContains()");
  int hash = getHash(key, t->size);
  if(t->table[hash] && hashListFind(t->table[hash], key))
    return true;
  return false;
}

char *tableGet(Table *t, char *key) {
  if(!t) autoError("NULL HashTable pased to tableGet()");
  int hash = getHash(key, t->size);
  if(!t->table[hash]) return NULL;
  return hashListFind(t->table[hash], key);
  /*for (HashListNode temp = t->table[hash]->first; temp; temp = temp->next) {
    if(!strcmp(temp->key, key)) return temp->value;
  }*/
}

int tableGetInt(Table *t, char *key) {
  char *value = tableGet(t, key);
  char extest[401] = {}; // this is one way to test ifsomething is an integer apparently
  sprintf(extest, "%d", atoi(value));
  if(!value || strcmp(extest, value)) return 0;
  return (atoi(value));
}

float tableGetFloat(Table *t, char *key) {
  char *value = tableGet(t, key);
  char extest[401] = {}; // this is one way to test ifsomething is a float apparently
  sprintf(extest, "%f", atof(value));
  if(!value || strcmp(extest, value)) return 0.0;
  return (atof(value));
}

bool tableGetBool(Table *t, char *key) {
  char *value = tableGet(t, key);
  if(!value) return false;
  return !strcmp(value, "true");
}

List *tableGetList(Table *t, char *key) {
  char *value = tableGet(t, key);
  if(!value) return NULL;
  List *l = listCreate();
  int count = 0;
  int i = 0;
  char tok[strlen(value)];
  while(value[count] != '\0') {
    for (i = 0; value[count] != ' ' && value[count] != '\0'; i++) {
      tok[i] = value[count++];
    }
    count++;
    tok[++i] = '\0';
    listAppend(l, tok);
    if(value[count - 1] == '\0') break; // account for the possibility of a string of size n + 2 followed by size n: '....\0' -> '...\0.\0'
  }
  return l;
}
/*
char **tableGetStringArray(Table *t, char *key) {
  char *value = tableGet(t, key);
  if(!value) return NULL;
  int vlen = strlen(value);
  int alen = 1; //start it at one for purposes of algorithm in use
  for (int i = 0; i < vlen; i++) {
    if(value[i] == ' ') alen++;
  }
  char **ns = calloc(alen, sizeof(char *));
  int cloc = 0; // current location in value
  for (int i = 0; i < alen; i++) {
    ns[i] = calloc(vlen, sizeof(char));
    for (int j = 0; cloc < vlen; j++) {
      if(value[cloc] == ' ') {
        ns[i][j] = '\0';
        cloc++;
        break;
      }
      ns[i][j] = value[cloc++];
    }
  }
  return ns;
}

void freeStringArray(char **sa) {
  int len = sizeof(sa)/sizeof(char *);
  for (int i = 0; i < len; i++) free(sa[i]);
  free(sa);
}
*/

void tablePut(Table *t, char *key, char *value) {
  if(!t) autoError("NULL HashTable passed to tablePut()");
  int hash = getHash(key, t->maxSize);
  if(!t->table[hash]) {
    t->table[hash] = hashListCreate();
  }
  //debugPrint("Hash position is %d", hash);
  //debugPrint("About to add %s with %s", key, value);
  if(hashListAdd(t->table[hash], key, value)) t->size++;
  //debugPrint("Added %s with %s", key, value);
}

void tableRemove(Table *t, char *key) {
  if(!t) autoError("Passed NULL Table to tableRemove()");
  int hash = getHash(key, t->size);
  if(!t->table[hash]) return;
  hashListRemove(t->table[hash], key);
}

void tableDestroy(Table *t) {
  int count = 0;
  for (int i = 0; i < t->size; i++) {
    if(!t->table[i]) continue;
    count += hashListDestroy(t->table[i]);
    if(count == t->size) break;
  }
  free(t->table);
  free(t->id);
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
  if(!l) autoError("NULL HashList passed to hashListDestroy()");
  int count = 0;
  if(!l->first) return count;
  if(!l->first->next) {
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
  if(!l) autoError("NULL HashList passed to hashListAdd()");
  //debugPrint("About to hashListRemove()");
  bool incsize = !hashListRemove(l, key);
  //debugPrint("hashListRemove() called");
  HashListNode *temp = malloc(sizeof(HashListNode));
  temp->key = calloc(101, sizeof(char));
  sprintf(temp->key, "%s", key);
  //debugPrint("Key is now %s", temp->key);
  temp->value = calloc(401, sizeof(char));
  sprintf(temp->value, "%s", value);
  if(!l->first || !l->last) {
    l->first = temp;
    l->last = l->first;
  } else {
    l->last->next = temp;
    l->last = l->last->next;
  }
  l->last->next = NULL;
  //debugPrint("New addition in HashList %s with %s", l->last->key, l->last->value);
  return incsize;
}

// returns whether or not something was actually removed
bool hashListRemove(HashList *l, char *key) {
  if(!l) autoError("NULL HashList passed to hashListRemove()");
  if(!l->first || !l->last) return false;
  if(!l->first->next) {
    //debugPrint("The first key is %s", l->first->key);
    if(!strcmp(l->first->key, key)) {
      free(l->first->key);
      free(l->first->value);
      free(l->first);
      l->first = NULL;
      l->last = NULL;
      return true;
    }
    //debugPrint("YOLOSWAG");
    return false;
  }
  //debugPrint("Almost halfway through");
  if(!strcmp(l->first->key, key)) {
    HashListNode *temp = l->first;
    l->first = l->first->next;
    free(temp->key);
    free(temp->value);
    free(temp);
    return true;
  }
  //debugPrint("Halfway");
  HashListNode *p = l->first;
  HashListNode *c = p->next;
  while(c) {
    if(!strcmp(c->key, key)) break;
    p = c;
    c = c->next;
  }
  if(!c) return false;
  if(c == l->last) l->last = p;
  p->next = c->next;
  free(c->key);
  free(c->value);
  free(c);
  return true;
}

char *hashListFind(HashList *l, char *key) {
  if(!l) autoError("NULL HashList passed to hashListFind()");
  for (HashListNode *temp = l->first; temp; temp = temp->next)
    if(!strcmp(key, temp->key))
      return temp->value;
  return NULL;
}

Table *tableCreate(int size) {
  Table *t = malloc(sizeof(Table));
  t->table = calloc(size, sizeof(HashList *));
  t->size = 0;
  t->maxSize = size;
  t->id = calloc(101, sizeof(char));
  return t;
}

Table *rehash(Table *t) {
  if(!t) autoError("NULL Table passed to rehash()");
  
 // Table n = tableCreate();
  return NULL;
}

int getHash(char *key, int len) {
  int hash;
  int  i;
  for (hash=0, i=0; i < strlen(key); i++) hash=hash^(int)key[i];
  return ((hash)%len);
}
