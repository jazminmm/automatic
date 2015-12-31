/*

  List.h

*/

#ifndef _LIST_H_
#define _LIST_H_

#include "Extra.h"

typedef struct Node {
  char *sdir;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct List {
  Node *first;
  Node *last;
} List;

// create a blank list
List *listCreate();

// create a list from a dirent struct (not including ".", and "..")
List *listCreateFromDirent(struct dirent **d, int ndir);

void listPrint(List *l);

int listGetSize(List *l);

//d is the struct dirent and ndir is the number of items in the struct
int listGetPos(List *l, Node *cur);

void listDestroy(List *l);

void listAppend(List *l, char *sdir);

List *listCopy(List *l);

void deleteNode(List *l, Node *n);

void listFilter(List *l, char *dir, char *filter);

// returns a list of directories based off listCreateFromDirent and the current directory
List *dirList();

#endif //_LIST_H_
