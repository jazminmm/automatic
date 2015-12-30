/*

  List.c

*/

#include "List.h"

List *listCreate(char **dirl, int ndir, char *path, int graded) {
  char temps[500];
  FILE *fp;
  int total = 0;
  List *n = malloc(sizeof(List));
  Node *temp = malloc(sizeof(Node));
  total++;
  temp->prev = NULL;
  n->graded = graded;
  n->first = NULL;
  int j = 2; // skip "." and ".."
  while(!n->first && j < ndir) {
    //    printf("test1\n");
    temp->sdir = dirl[j];
    sprintf(temps, "/afs/cats.ucsc.edu/class/cmps012b-pt.w15/%s/%s/grade.txt", path, temp->sdir);
    fp = fopen(temps, "r"); //check whether or not a directory is graded
    temp->graded = fp ? 1 : 0;
    if ((fp && n->graded == 1) || (!fp && n->graded == 0) || (n->graded == 2)) {
      n->first = temp; //if we are done checking conditions then we may move onto the next nodes
    }
    if (fp) fclose(fp);
    if (j + 1 < ndir - 1) {
      j++; // don't increment j if dirl[j+1] doesn't exist
    }
    else if ((temp->graded == 0 && n->graded == 1) || (temp->graded == 1 && n->graded == 0)) {
      free(temp);
      total--;
      free(n);
      return NULL;
    }
  }
  if (j + 1 == ndir) {
    n->last = temp;
    return n;
  }
  for (int i = j; i < ndir - 1; i++) {
    //    printf("test2\n");
    temp->next = malloc(sizeof(Node));
    total++;
    temp->next->prev = temp;
    temp = temp->next;
    while(i < ndir - 1) {
      temp->sdir = dirl[i]; // recall that the first two directories are "." and then ".."
      //printf("testing: %s\n", dirl[i]);
      sprintf(temps, "/afs/cats.ucsc.edu/class/cmps012b-pt.w15/%s/%s/grade.txt", path, temp->sdir);
      fp = fopen(temps, "r"); //once again we are checking if the directory is graded
      temp->graded = fp ? 1 : 0;
      if ((fp && n->graded == 1) || (!fp && n->graded == 0) || n->graded == 2) {
        if (fp) fclose(fp);
        break;
      }
      if (fp) fclose(fp);
      i++;
    }
    //printf("testing directory currently is: %s\n", temp->sdir);
  }
  if ((temp->graded == 0 && n->graded == 1) || (temp->graded == 1 && n->graded == 0)) { // special way of dealing with not needing a node, instead of deleting and recreating later, we reuse
    temp = temp->prev;
    free(temp->next);
    total--;
  }
  j = ndir - 1;
  temp->next = malloc(sizeof(Node));
  temp->next->prev = temp;
  total++;
  temp = temp->next;
  temp->sdir = dirl[j];
  sprintf(temps, "/afs/cats.ucsc.edu/class/cmps012b-pt.w15/%s/%s/grade.txt", path, temp->sdir);
  fp = fopen(temps, "r");
  temp->graded = fp ? 1 : 0;
  if ((fp && n->graded == 1) || (!fp && n->graded == 0) || n->graded == 2) {
    n->last = temp;
    temp->next = NULL;
  } else {
    n->last = temp->prev;
    n->last->next = NULL;
    free(temp);
    total--;
  }
  if (fp) fclose(fp);
  //printf("Alloced %d nodes and a list\n", total);
  return n;
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

void listAppend(List *l, char *sdir, int graded) { //buggy
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
  char temps[501];
  strncpy(temps, sdir, 500);
  temp->sdir = temps;
  temp->graded = graded;
}

List *listCopy(List *l) { //buggy
  List *n = malloc(sizeof(List));
  n->graded = l->graded;
  if (!listGetSize(l)) return n;
  Node *temp = l->first;
  while (temp) {
    listAppend(n, temp->sdir, temp->graded);
  }
  return n;
}

void deleteNode(List *l, Node *n) {
  if (!n) return;
  if (n == l->first) l->first = (n->next ? n->next : NULL);
  if (n == l->last) l->last = (n->prev ? n->prev : NULL);
  if (n->prev) n->prev->next = n->next;
  if (n->next) n->next->prev = n->prev;
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
