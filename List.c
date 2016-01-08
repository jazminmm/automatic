/*

   List.c

 */

#include "List.h"

List *listCreate() {
  List *l = malloc(sizeof(List));
  l->first = NULL;
  l->last = NULL;
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
    if ((fp && mode) || (!fp && !mode)) {
      Node *temp1 = temp->next;
      listRemove(l, temp->sdir);
      temp = temp1;
      fcount++;
    } else temp = temp->next;
    if (fp) fclose(fp);
  }
  printf("Successfully filtered out %d directories\n", fcount);
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
  if (!fp) {
    printf("%s.autotable didn't exist when calling listRead()\n", id);
    exit(1);
  }
  while(fgets(temp, 500, fp)) {
    listAppend(l, temp);
  }
  fclose(fp);
  return l;
}

void listWrite(List *l) {
  char temp[501];
  char *id = listGetID(l);
  if (!id) {
    printf("List with no set ID passed to listWrite()\n");
    exit(1);
  }
  sprintf(temp, "%s.autolist", id);
  FILE *fp = fopen(temp, "w");
  for (Node *tempn = l->first; tempn; tempn = tempn->next) {
    fprintf(fp, "%s\n", tempn->sdir);
  }
  fclose(fp);
  listDestroy(l);
}

void listRemove(List *l, char *sdir) {
  if (!l) {
    printf("Passed NULL List to listRemove()\n");
    exit(1);
  }
  if (!listContains(l, sdir)) {
    printf("Tried to remove a non-existent String in listRemove()\n");
    exit(1);
  }
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
  if (!l) {
    printf("Passed NULL List to listContains()\n");
    exit(1);
  }
  for (Node *temp = l->first; temp; temp = temp->next) {
    if (!strcmp(temp->sdir, sdir)) return true;
  }
  return false;
}

void listString(List *l, char *buf) {
  if (!l) {
    printf("Passed NULL List to listString()\n");
    exit(1);
  }
  strncpy(buf, "", strlen(buf));
  if (!l->first) return;
  for (Node *n = l->first; n; n = n->next) {
    strcat(buf, n->sdir);
    strcat(buf, "\n");
  }
  //return;
}
