//Stack.c

#include "Stack.h"

Stack *createStack() {
  Stack *n = malloc(sizeof(Stack));
  n->size = 0;
  n->top = NULL;
  return n;
}

void pushStack(Stack *s, char *data) {
  if (!s) {
    printf("Null Stack given to pushStack()\n");
    exit(1);
  }
  if (!data) {
    printf("Null String given to pushStack()\n");
    exit(1);
  }
  StackItem *temp = malloc(sizeof(StackItem));
  if (!s->top) {
    s->top = temp;
    temp->next = NULL;
  } else {
    temp->next = s->top;
    s->top = temp;
  }
  temp->data = data;
  s->size++;
}

char *popStack(Stack *s) {
  if (!s) {
    printf("Null Stack given to popStack()\n");
    exit(1);
  }
  if (s->size < 1) {
    printf("Tried to pop an empty Stack in popStack()\n");
    exit(1);
  } else {
    char *temp = s->top->data;
    StackItem *ti = s->top;
    s->top = s->top->next;
    free(ti);
    s->size--;
    return temp;
  }
}
