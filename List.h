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
  char *id;
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

void listPrepend(List *l, char *sdir);

// this inserts into the list in such a way that keeps the list in alphabetical order
void listInsert(List *l, char *sdir);

List *listCopy(List *l);

void deleteNode(Node *n);

void listFilter(List *l, char *dir, char *filter);

// returns a list of directories based off listCreateFromDirent and the current directory
List *dirList();

// sets the id of l to be id
void listSetID(List *l, char *id);

// returns the id or NULL if one hasn't been set
char *listGetID(List *l);

// returns a List that contains all Strings in id.autolist. Also sets the list's id to id
List *listRead(char *id);

// writes a list to it's 
void listWrite(List *l);

// Removes sdir from L
void listRemove(List *l, char *sdir);

// Returns whether L contains sdir
bool listContains(List *l, char *sdir);

// overwrites buf to be listPrint as a String
void listString(List *l, char *buf);

#endif //_LIST_H_
