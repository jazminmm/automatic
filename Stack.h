//Stack.h

#ifndef _STACK_H_
#define _STACK_H_

#include "Extra.h"

typedef struct StackItem {
  struct StackItem *next;
  char *data;
} StackItem;

typedef struct Stack {
  StackItem *top;
  int size;
} Stack;

// Creates a Stack and returns a pointer to it
Stack *createStack();

// Pushes a String onto the stack
void pushStack(Stack *s, char *data);

// Pops a String off of the stack. Program will crash if Stack is empty
char *popStack(Stack *s);

#endif //_STACK_H_

