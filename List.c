/*

   List.c

 */

#include "List.h"

List *listCreate() {
  List *l = malloc(sizeof(List));
  l->first = NULL;
  l->last = NULL;
  l->cur = NULL;
  l->id = calloc(101, sizeof(char));
  return l;
}

//d is the struct dirent and ndir is the number of items in the struct
List *listCreateFromDirent(struct dirent **d, int ndir) {
  List *l = listCreate();
  for (int i = 0; i < ndir; i++) if (strncmp(".", d[i]->d_name, 2) && strncmp("..", d[i]->d_name, 3)) {
    if (chdir(d[i]->d_name) == 0) {
      chdir("..");
      listAppend(l, d[i]->d_name);
    }
  }
  return l;
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

int listGetPos(List *l) {
  if (!l) autoError("NULL list passed to listGetPos()", NULL);
  if (!l->cur) {
    return -1;
  }
  int total = 1;
  for(Node *temp = l->first; temp && temp != l->cur; temp = temp->next) total++;
  return total;
}

void listDestroy(List *l) {
  if (!l) return;
  if (l->first == l->last) {
    deleteNode(l->first);
    free(l);
    return;
  }
  int total = 0;
  Node *temp;
  for(temp = l->first->next; temp->next; temp = temp->next) {
    deleteNode(temp->prev);
    total++;
    //printf("%s\n", temp->sdir);
  }
  deleteNode(temp->prev);
  total++;
  deleteNode(temp);
  total++;
  free(l->id);
  free(l);
  //printf("freed %d Nodes and a list\n", total);
}

void listPrepend(List *l, char *sdir) {
  Node *temp = l->first;
  if (!temp) {
    l->first = malloc(sizeof(Node));
    l->last = l->first;
    temp = l->first;
    temp->next = NULL;
  } else {
    temp->prev = malloc(sizeof(Node));
    temp = temp->prev;
    temp->next = l->first;
    l->first = temp;
  }
  temp->prev = NULL;
  char *temps = calloc(501, sizeof(char));
  strncpy(temps, sdir, 500);
  temp->sdir = temps;
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

void listInsert(List *l, char *sdir) {
  Node *temp = l->first;
  if (!temp) {
    listAppend(l, sdir);
    return;
  }
  if (strncmp(temp->sdir, sdir, max(strlen(sdir), strlen(temp->sdir))) < 0) {
    listPrepend(l, sdir);
    return;
  }
  temp = temp->next;
  while(temp && strncmp(temp->sdir, sdir, max(strlen(sdir), strlen(temp->sdir))) > 0) {
    temp = temp->next;
  }
  if (!temp) {
    listAppend(l, sdir);
    return;
  }
  Node *temp2 = malloc(sizeof(Node));
  temp->prev->next = temp2;
  temp2->prev = temp->prev;
  temp->prev = temp2;
  temp2->next = temp;
  char *temps = calloc(501, sizeof(char));
  strncpy(temps, sdir, 500);
  temp->sdir = temps;
}

List *listCopy(List *l) {
  List *n = listCreate();
  if (!listGetSize(l)) return n;
  Node *temp = l->first;
  while (temp) {
    listAppend(n, temp->sdir);
  }
  sprintf(n->id, "%s", l->id);
  return n;
}

void deleteNode(Node *n) {
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
    if ((fp && mode) || (!fp && !mode)) {
      fcount++;
    }
    temp = temp->next;
    if (fp) fclose(fp);
  }
  if (fcount == listGetSize(l)) {
    autoWarn("Filter wasn't applied because it would've deleted the entire list", NULL);
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
    if ((fp && mode) || (!fp && !mode)) {
      Node *temp1 = temp->next;
      listRemove(l, temp->sdir);
      temp = temp1;
      fcount++;
    } else temp = temp->next;
    if (fp) fclose(fp);
  }
  autoPrint("Successfully filtered out %d directories", fcount);
}

List *dirList() {
  struct dirent **fileList = NULL;
  int ndir = scandir(".", &fileList, NULL, alphasort);
  List *l = listCreateFromDirent(fileList, ndir);
  for (int i = 0; i < ndir; i++) free (fileList[i]);
  free (fileList);
  return l;
}

void listSetID(List *l, char *id) {
  sprintf(l->id, "%s", id);
}

char *listGetID(List *l) {
  return (l->id[0] == '\0' ? NULL : l->id);
}

List *listRead(char *id) {
  List *l = listCreate();
  listSetID(l, id);
  char temp[501];
  sprintf(temp, "%s.autolist", id);
  FILE *fp = fopen(id, "r");
  if (!fp) autoError("%s.autotable didn't exist when calling listRead()", id);
  while(fgets(temp, 500, fp)) {
    listAppend(l, temp);
  }
  fclose(fp);
  return l;
}

void listWrite(List *l) {
  char temp[501];
  char *id = listGetID(l);
  if (!id) autoError("List with no set ID passed to listWrite()", NULL);
  sprintf(temp, "%s.autolist", id);
  FILE *fp = fopen(temp, "w");
  for (Node *tempn = l->first; tempn; tempn = tempn->next) {
    fprintf(fp, "%s\n", tempn->sdir);
  }
  fclose(fp);
  listDestroy(l);
}

void listRemove(List *l, char *sdir) {
  if (!l) printf("Passed NULL List to listRemove()", NULL);
  if (!listContains(l, sdir)) autoError("Tried to remove a non-existent String %s in listRemove()", sdir);
  Node *temp = NULL;
  for (temp = l->first; temp; temp = temp->next) {
    if (!strcmp(temp->sdir, sdir)) break;
  }
  if (temp == l->first) l->first = l->first->next;
  if (temp == l->last) l->last = l->last->prev;
  if (temp->prev) temp->prev->next = temp->next;
  if (temp->next) temp->next->prev = temp->prev;
  deleteNode(temp);
}

bool listContains(List *l, char *sdir) {
  if (!l) autoError("Passed NULL List to listContains()", NULL);
  for (Node *temp = l->first; temp; temp = temp->next) {
    if (!strcmp(temp->sdir, sdir)) return true;
  }
  return false;
}

void listString(List *l, char *buf) {
  if (!l) autoError("Passed NULL List to listString()", NULL);
  strncpy(buf, "", strlen(buf));
  if (!l->first) return;
  for (Node *n = l->first; n; n = n->next) {
    strcat(buf, n->sdir);
    strcat(buf, "\n");
  }
  //return;
}

bool listMoveFront(List *l) {
  if (!l) autoError("NULL List passed to listMoveFront()", NULL);
  if (listGetSize(l) == 0) {
    //printf("Can't set current in an empty list\n");
    return false;
  }
  l->cur = l->first;
  return true;
}

bool listMoveBack(List *l) {
  if (!l) autoError("NULL List passed to listMoveBack()", NULL);
  if (listGetSize(l) == 0) {
    //printf("Can't set current in an empty list\n");
    return false;
  }
  l->cur = l->last;
  return true;
}

bool listMoveNext(List *l) {
  if (!l) autoError("NULL List passed to listMoveNext()", NULL);
  if (!l->cur) {
    //printf("Can't move current relative to itself if it is NULL\n");
    return false;
  }
  if (listGetPos(l) == listGetSize(l)) {
    //printf("Already at back of list\n");
    return false;
  }
  l->cur = l->cur->next;
  return true;
}

bool listMovePrev(List *l) {
  if (!l) autoError("NULL List passed to listMovePrev()", NULL);
  if (!l->cur) {
    //printf("Can't move current relative to itself if it is NULL\n");
    return false;
  }
  if (listGetPos(l) == 1) {
    //printf("Already at front of list\n");
    return false;
  }
  l->cur = l->cur->prev;
  return true;
}

char *listGetCur(List *l) {
  if (!l) autoError("NULL List passed to listGetCur()", NULL);
  if (!l->cur) return NULL;
  return l->cur->sdir;
}

void listConcat(List *first, List *second) {
  if (!first) autoError("first List in listConcat() is NULL", NULL);
  if (!second) autoError("second List in listConcat() is NULL", NULL);
  for (listMoveFront(second); listGetCur(second); listMoveNext(second)) {
    listAppend(first, listGetCur(second));
  }
  listDestroy(second);
}
