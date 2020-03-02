#include <stdio.h>
#include "node.h"

// Linked-list based stack.
struct Stack
{
  struct Node *top;
  size_t lenght;
};

// Creates stack struct.
struct Stack *createstack(struct Node *initnode);
// Return stack lenght.
size_t isempty(struct Stack *stack);
// Pushes a element ref
void push(struct Stack *stack, struct Node *newtop);
// Return top element ref; needs to be free after usage.
struct Node *pop(struct Stack *stack);
// Return ref to the top element; no deleting it.
struct Node *peek(struct Stack *stack);
// ToString implementation
void printstack(struct Stack *stack);
