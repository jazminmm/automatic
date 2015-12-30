/*

  List.c

*/

#include "List.h"

//d is the struct dirent and ndir is the number of items in the struct
List *listCreate(struct dirent **d, int ndir) {
  List *l = malloc(sizeof(List));
  l->first = NULL;
  l->last = NULL;
  for (int i = 2; i < ndir; i++) listAppend(l, d[i]->d_name);
}

void listPrint(List *l) {
  for (Node *temp = l->first; temp; temp = temp->next) printf("%s ", temp->sdir);
  printf("\n");
}

int listGetSize(List *l) {
  int total = 0;
  for (Node *temp = l->first; temp; temp = temp->next) total++;
  return total;
}

int listGetPos(List *l, Node *cur) {
  int total = 0;
  for(Node *temp = l->first; temp->next && temp != cur; temp = temp->next) total++;
  return total + 1;
}

void listDestroy(List *l) {
  if (!l) return;
  if (l->first == l->last) {
    free(l->first);
    free(l);
    return;
  }
  int total = 0;
  Node *temp;
  for(temp = l->first->next; temp->next; temp = temp->next) {
    free(temp->prev);
    total++;
    //printf("%s\n", temp->sdir);
  }
  free(temp->prev);
  total++;
  free(temp);
  total++;
  free(l);
  //printf("freed %d Nodes and a list\n", total);
}

void listAppend(List *l, char *sdir) {
  Node *temp = l->last;
  if (!temp) {
    l->first = malloc(sizeof(Node));
    l->last = l->first;
    temp = l->first;
    temp->prev = NULL;
  } else {
    temp->next = malloc(sizeof(Node));
    temp = temp->next;
    temp->prev = l->last;
    l->last = temp;
  }
  temp->next = NULL;
  char *temps = calloc(501, sizeof(char));
  strncpy(temps, sdir, 500);
  temp->sdir = temps;
}

List *listCopy(List *l) {
  List *n = malloc(sizeof(List));
  n->first = NULL;
  n->last = NULL;
  if (!listGetSize(l)) return n;
  Node *temp = l->first;
  while (temp) {
    listAppend(n, temp->sdir);
  }
  return n;
}

void deleteNode(List *l, Node *n) {
  if (!n) return;
  if (n == l->first) l->first = (n->next ? n->next : NULL);
  if (n == l->last) l->last = (n->prev ? n->prev : NULL);
  if (n->prev) n->prev->next = n->next;
  if (n->next) n->next->prev = n->prev;
  free(n->sdir);
  free(n);
}

void listFilter(List *l, char *dir,  char *filter) {
  if (strlen(filter) < 2) return;
  int fcount = 0;
  int mode = (filter[0] == '!' ? 1 : 0);
  if (mode == 1) filter = filter + 1;
  Node *temp = l->first;
  char temps[501];
  char loc[501];
  while(temp) {
    strncpy(temps, filter, 500);
    temps[strlen(temps) - 1] = '\0';
    sprintf(loc, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s/%s", dir, temp->sdir);
    chdir(loc);
    FILE *fp = fopen(temps, "r");
    //sprintf(loc, "ls /afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s/%s", dir, temp->sdir); // testing
    //system(loc);      // testing
    //printf("In directory %s file %s %s but it %s in the filtered list\n", temp->sdir, temps, fp ? "exists" : "doesn't exist", !mode ? "should exist" : "shouldn't exist");
    if (fp && mode || !fp && !mode) {
      fcount++;
    }
    temp = temp->next;
    if (fp) fclose(fp);
  }
  if (fcount == listGetSize(l)) {
    printf("Filter wasn't applied because it would've deleted the entire list\n");
    return;
  }
  fcount = 0;
  temp = l->first;
  while(temp) {
    strncpy(temps, filter, 500);
    temps[strlen(temps) - 1] = '\0';
    sprintf(loc, "/afs/cats.ucsc.edu/class/cmps012b-pt.s15/%s/%s", dir, temp->sdir);
    chdir(loc);
    FILE *fp = fopen(temps, "r");
    //printf("In directory %s file %s %s but it %s in the filtered list\n", temp->sdir, temps, fp ? "exists" : "doesn't exist", !mode ? "should exist" : "shouldn't exist");
    if (fp && mode || !fp && !mode) {
      Node *temp1 = temp->next;
      deleteNode(l, temp);
      temp = temp1;
      fcount++;
    } else temp = temp->next;
    if (fp) fclose(fp);
  }
  printf("Successfully filtered out %d directories\n", fcount);
}
