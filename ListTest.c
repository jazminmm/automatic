#include "List.h"

int main (int argc, char **argv) {

  List *l = listCreate();
  printf("listCreate() 1 successfull\n");
  listAppend(l, "one");
  listAppend(l, "two");
  listAppend(l, "three");
  listPrint(l);
  listPrepend(l, "zero");
  listPrint(l);
  listDestroy(l);
  printf("listDestroy() 1 successfull\n");
}
