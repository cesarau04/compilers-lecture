#include "stack.h"
#include <stdlib.h>

struct Stack *createstack(struct Node *initnode)
{
  struct Stack *newstack = malloc(sizeof(struct Stack));
  if (newstack == NULL)
    return NULL;

  newstack->top = malloc(sizeof(struct Node *));
  if (newstack->top == NULL)
  {
    free(newstack);
    return NULL;
  }

  if (initnode == NULL)
  {
    newstack->top == NULL;
    newstack->lenght = 0;
  }
  else
  {
    newstack->top = initnode;
    newstack->lenght = 1;
  }

  return newstack;
}

size_t isempty(struct Stack *stack)
{
  return (stack->lenght == 0 ? 1 : 0);
}

void push(struct Stack *stack, struct Node *newtop)
{
  // is this even needed?
  if (stack->top == NULL)
  {
    free(newtop->below);
  }
  else
  {
    newtop->below = stack->top;
  }
  stack->top = newtop;
  stack->lenght++;
}

struct Node *pop(struct Stack *stack)
{
  if (isempty(stack))
  {
    return NULL;
  }
  struct Node *ref = stack->top;
  if (stack->top->below != NULL)
  {
    stack->top = stack->top->below;
  }
  else
  {
    stack->top = NULL;
  }
  stack->lenght--;
  return ref;
}

struct Node *peek(struct Stack *stack)
{
  if (isempty(stack))
  {
    return NULL;
  }
  return stack->top;
}

void printstack(struct Stack *stack)
{
  struct Node *currentnode = peek(stack);
  while ((currentnode != NULL))
  {
    printf("val: %c\n", currentnode->value);
    currentnode = currentnode->below;
  }
}
