/*

  List.h

*/

#ifndef _LIST_H_
#define _LIST_H_

#include "Extra.h"

typedef struct Node {
  char *sdir;
  int graded; // 1 = yes, 0 = no
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct List {
  Node *first;
  Node *last;
  int graded; //1 = yes, 0 = no, 2 - mixed
} List;

List *listCreate(char **dirl, int ndir, char *path, int graded);

void listPrint(List *l);

int listGetSize(List *l);

int listGetPos(List *l);

void listDestroy(List *l);

void listAppend(List *l, char *sdir, int graded); //buggy

List *listCopy(List *l); //buggy

void deleteNode(List *l, Node *n);

void listFilter(List *l, char *dir, char *filter);

#endif //_LIST_H_
