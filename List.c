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
List *listCreateFromDirent(struct dirent **d, int ndir, int mustFolder) {
  List *l = listCreate();
  for (int i = 0; i < ndir; i++) {
    if(strncmp(".", d[i]->d_name, 2) && strncmp("..", d[i]->d_name, 3)) { // don't include ".", and ".." directories
      if(mustFolder && chdir(d[i]->d_name) == 0) {
        chdir("..");
        listAppend(l, d[i]->d_name);
      } else if (!mustFolder) {
        listAppend(l, d[i]->d_name);
      }
    }
  }
  return l;
}

List *listCreateFromToken(char *str, const char *delimiters) {
  if(!str || !delimiters || !strcmp(delimiters, "")) {
    //debugPrint("str is size %d and delimiters is size %d", strlen(str), strlen(delimiters));
    debugPrint("One of the arguments to listCreateFromToken() is NULL or an empty String");
    return NULL;
  }
  char temps[5001] = ""; // holds the current token
  int tpos = 0; // current position in token buffer
  List *l = listCreate();
  for (int i = 0; 1; i++) { // go to next character of string to parse
    for (int j = 0; j < strlen(delimiters); j++) { // check if character is one of the delimiters
      if (tpos > 5000) autoError("Token has surpassed capacity in listCreateFromToken()");
      if (i >= strlen(str)) break; // this is a valid exit condition of the loop
      if(str[i] == delimiters[j]) {
        temps[tpos] = '\0'; // string ends at a null character
        tpos = 0;
        listAppend(l, temps);
        i++; // this line and the next work together to emulate starting checks on the next character
        j = 0; // this must be done here to work with the logic of this algorithm
      }
    }
    if (i >= strlen(str)) break; // this is the real exit condition of this loop
    temps[tpos++] = str[i];
  }
  temps[tpos] = '\0'; // ends string at null
  if (tpos) listAppend(l, temps); // without this, the remaining piece of the string, if any, would be forgotten
  return l;
}

void listPrint(List *l) {
  if (!l) autoError("NULL List passed to listPrint()");
  for (Node *temp = l->first; temp; temp = temp->next) printf("%s ", temp->sdir);
  printf("\n");
}

int listGetSize(List *l) {
  if (!l) autoError("NULL List passed to listGetSize()");
  int total = 0;
  for (Node *temp = l->first; temp; temp = temp->next) total++;
  return total;
}

int listGetPos(List *l) {
  if(!l) autoError("NULL List passed to listGetPos()");
  if(!l->cur) {
    return -1;
  }
  int total = 1;
  for(Node *temp = l->first; temp && temp != l->cur; temp = temp->next) total++;
  return total;
}

void listDestroy(List *l) {
  if (!l) autoError("NULL List passed to listDestroy()");
  if (!l->first) {
    free(l->id);
    free(l);
    return;
  }
  if(l->first == l->last) {
    deleteNode(l->first);
    free(l->id);
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
  if (!l) autoError("NULL List passed to listPrepend()");
  Node *temp = l->first;
  if(!temp) {
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
  char *temps = calloc(5001, sizeof(char));
  strncpy(temps, sdir, 5000);
  temp->sdir = temps;
}

void listAppend(List *l, char *sdir) {
  if (!l) autoError("NULL List passed to listPrepend()");
  Node *temp = l->last;
  if(!temp) {
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
  char *temps = calloc(5001, sizeof(char));
  strncpy(temps, sdir, 5000);
  temp->sdir = temps;
}

void listInsert(List *l, char *sdir) {
  if (!l) autoError("NULL List passed to listInsert()");
  Node *temp = l->first;
  if(!temp) {
    listAppend(l, sdir);
    return;
  }
  if(strncmp(temp->sdir, sdir, max(strlen(sdir), strlen(temp->sdir))) < 0) {
    listPrepend(l, sdir);
    return;
  }
  temp = temp->next;
  while(temp && strncmp(temp->sdir, sdir, max(strlen(sdir), strlen(temp->sdir))) > 0) {
    temp = temp->next;
  }
  if(!temp) {
    listAppend(l, sdir);
    return;
  }
  Node *temp2 = malloc(sizeof(Node));
  temp->prev->next = temp2;
  temp2->prev = temp->prev;
  temp->prev = temp2;
  temp2->next = temp;
  char *temps = calloc(5001, sizeof(char));
  strncpy(temps, sdir, 5000);
  temp->sdir = temps;
}

List *listCopy(List *l) {
  List *n = listCreate();
  if(!listGetSize(l)) return n;
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
  debugPrint("listFilter() is broken and currently unapplicable");
  if (1) return;
  if (!l) autoError("Null List passed to listFilter");
  if (!dir) autoError("Null, directory passed to listFilter");
  if (!filter) autoError("Null filter passed to listFilter");

  if (!chdir(dir)) {
    debugPrint("Directory %s doesn't exist", dir);
    return;
  }
  int mode = filter[0] == '!' ? 0 : 1; // if mode is 1 then we want a list with the file, else we want a list without it
  filter += filter[0] == '!' ? 1 : 0; // pointer moves over the '!' if it exists
  int count = 0;
  if (listMoveFront(l)) autoError("List was empty in listFilter()");
  while(1) {
    if (!chdir(listGetCur(l))) {
      FILE *fp = fopen(filter, "r");
      if (mode) {
        if(fp) fclose(fp);
        else count++;
      } else {
        if (fp) {
          fclose(fp);
          count++;
        }
      }
    }
    chdir("..");
    if(!listMoveNext(l)) break;
  }
  if (count == listGetSize(l)) {
    debugPrint("listFilter aborted because it would've resulted in an empty list");
    return;
  }
  listMoveFront(l);
  while(1) {
    if (!chdir(listGetCur(l))) {
      FILE *fp = fopen(filter, "r");
      if (mode) {
        if(fp) fclose(fp);
        else listRemove(l, listGetCur(l));
      } else {
        if (fp) {
          fclose(fp);
          listRemove(l, listGetCur(l));
        }
      }
    }
    chdir("..");
    if(!listMoveNext(l)) break;
  }

  debugPrint("listFilter filtered %d directories", count);

  return; // ignore the rest
/*

  if(strlen(filter) < 2) return;
  int fcount = 0;
  int mode = (filter[0] == '!' ? 1 : 0);
  if(mode == 1) filter = filter + 1;
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
    if((fp && mode) || (!fp && !mode)) {
      fcount++;
    }
    temp = temp->next;
    if(fp) fclose(fp);
  }
  if(fcount == listGetSize(l)) {
    autoWarn("Filter wasn't applied because it would've deleted the entire list");
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
    if((fp && mode) || (!fp && !mode)) {
      Node *temp1 = temp->next;
      listRemove(l, temp->sdir);
      temp = temp1;
      fcount++;
    } else temp = temp->next;
    if(fp) fclose(fp);
  }
  autoPrint("Successfully filtered out %d directories", fcount);
*/
}

void listItemConcat(List *l, const char *format) {
  if(!l) autoError("NULL List passed to listItemConcat()");
  if(!format) autoError("NULL String passed to listItemConcat()");
  char temp[5001] = "";
  int repinst = -1;
  for (int i = 0; i < strlen(format); i++)
    if(format[i] == '%' && format[i+1] == 's') {
      if (repinst != -1)
        autoError("String contains more than one instance of \"\%s\" in listItemConcat()");
      repinst = i;
      break;
    }
  if(repinst == -1) autoError("String doesn't contain \"\%s\" in listItemConcat()");
  if(!listMoveFront(l)) return;
  while(1) {
    sprintf(temp, format, listGetCur(l));
    /*
       if(repinst) strncpy(temp, format, repinst);
       temp[repinst] = '\0';
       strcat(temp, listGetCur(l));
       strcat(temp, format + repinst + 2); // nothing like a little pointer arithmatic to help
    // you sleep at night
     */
    listSetCur(l, temp);

    if(!listMoveNext(l)) return;
  }
}

List *dirList(char *id, int mustFolder) {
  struct dirent **fileList = NULL;
  int ndir = scandir(".", &fileList, NULL, alphasort);
  List *l = listCreateFromDirent(fileList, ndir, mustFolder);
  listSetID(l, id);
  for (int i = 0; i < ndir; i++) {
    free (fileList[i]);
  }
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
  char temp[5001];
  sprintf(temp, "%s.autolist", id);
  FILE *fp = fopen(temp, "r");
  if(!fp) autoError("%s.autolist didn't exist when calling listRead()", id);
  while(fgets(temp, 5000, fp)) {
    if (temp[strlen(temp) - 1] == '\n') temp[strlen(temp) - 1] = '\0';
    if (!strlen(temp)) continue; // get rid of newlines in strings, don't append
                                 // empty strings to the list
    listAppend(l, temp);
  }
  fclose(fp);
  return l;
}

void listWrite(List *l) {
  char temp[5001];
  char *id = listGetID(l);
  if(!id) autoError("List with no set ID passed to listWrite()");
  sprintf(temp, "%s.autolist", id);
  FILE *fp = fopen(temp, "w");
  for (Node *tempn = l->first; tempn; tempn = tempn->next) {
    fprintf(fp, "%s\n", tempn->sdir);
  }
  fclose(fp);
  listDestroy(l);
}

void listRemove(List *l, char *sdir) {
  if(!l) printf("Passed NULL List to listRemove()");
  if(!listContains(l, sdir)) autoError("Tried to remove a non-existent String %s in listRemove()", sdir);
  Node *temp = NULL;
  for (temp = l->first; temp; temp = temp->next) {
    if(!strcmp(temp->sdir, sdir)) break;
  }
  if(temp == l->first) l->first = l->first->next;
  if(temp == l->last) l->last = l->last->prev;
  if(temp->prev) temp->prev->next = temp->next;
  if(temp->next) temp->next->prev = temp->prev;
  deleteNode(temp);
}

bool listContains(List *l, char *sdir) {
  if(!l || !sdir) autoError("Passed NULL List or NULL string to listContains()");
  for (Node *temp = l->first; temp; temp = temp->next) {
    if(!strcmp(temp->sdir, sdir)) return true;
  }
  return false;
}

bool listSeek(List *l, char *sdir) {
  if(!l || !sdir) autoError("Passed NULL List or NULL string to listSeek()");
  Node *temp = l->cur;
  if (!listMoveFront(l)) return false;
  do {
    if(!strcmp(listGetCur(l), sdir)) return true;
  } while (listMoveNext(l));
  l->cur = temp;
  return false;
}

void listString(List *l, char *buf) {
  debugPrint("listString is deprecated and doesn't function");
  if (1) return;
  if(!l) autoError("Passed NULL List to listString()");
  buf[0] = '\0';
  if(!l->first) return;
  for (Node *n = l->first; n; n = n->next) {
    strcat(buf, n->sdir);
    strcat(buf, "\n");
  }
  //return;
}

bool listMoveFront(List *l) {
  if(!l) autoError("NULL List passed to listMoveFront()");
  if(listGetSize(l) == 0) {
    //printf("Can't set current in an empty list\n");
    l->cur = NULL;
    return false;
  }
  l->cur = l->first;
  return true;
}

bool listMoveBack(List *l) {
  if(!l) autoError("NULL List passed to listMoveBack()");
  if(listGetSize(l) == 0) {
    //printf("Can't set current in an empty list\n");
    l->cur = NULL;
    return false;
  }
  l->cur = l->last;
  return true;
}

bool listMoveNext(List *l) {
  if(!l) autoError("NULL List passed to listMoveNext()");
  if(!l->cur) {
    autoError("Can't move current relative to itself if it is NULL\n");
    return false;
  }
  if(listGetPos(l) == listGetSize(l)) {
    //printf("Already at back of list\n");
    l->cur = NULL;
    return false;
  }
  l->cur = l->cur->next;
  return true;
}

bool listMovePrev(List *l) {
  if(!l) autoError("NULL List passed to listMovePrev()");
  if(!l->cur) {
    autoError("Can't move current relative to itself if it is NULL\n");
    return false;
  }
  if(listGetPos(l) == 1) {
    //printf("Already at front of list\n");
    l->cur = NULL;
    return false;
  }
  l->cur = l->cur->prev;
  return true;
}

char *listGetCur(List *l) {
  if(!l) autoError("NULL List passed to listGetCur()");
  if(!l->cur) return NULL;
  //debugPrint("SWAG %s", l->cur->sdir);
  return l->cur->sdir;
}

void listSetCur(List *l, char *ns) {
  if(!l) autoError("NULL List passed to listSetCur()");
  if(!ns) autoError("NULL String passed to listSetCur()");
  if(!l->cur) return;
  strcpy(l->cur->sdir, ns);
}

void listConcat(List *first, List *second) {
  if(!first) autoError("first List in listConcat() is NULL");
  if(!second) autoError("second List in listConcat() is NULL");
  //char temp1[501], temp2[501];
  //listString(first, temp1);
  //listString(second, temp2);
  //debugPrint("List1 is size %d and list2 is size %d", listGetSize(first), listGetSize(second));
  //debugPrint("The two lists are\nlist1:\n%slist2:\n%s", temp1, temp2);
  listMoveFront(second);
  while (listGetCur(second)) {
    listAppend(first, listGetCur(second));
    listMoveNext(second);
  }
  listDestroy(second);
}
