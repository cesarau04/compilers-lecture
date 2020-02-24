#include <stdio.h>
#include <stdlib.h>

// Base struct inside a stack
struct Node
{
  struct Node *below;
  char value;
  size_t line;
  size_t column;
};

// Linked-list based stack.
struct Stack
{
  struct Node *top;
  size_t lenght;
};

// Creates stack struct.
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

// Return stack lenght.
size_t isempty(struct Stack *stack)
{
  return (stack->lenght <= 0 ? 1 : 0);
}

// Pushes a element ref.
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

// Return top element ref; needs to be free after usage.
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

// Return ref to the top element.
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

struct Node *createnode(char value, size_t line, size_t column)
{
  struct Node *newnode = malloc(sizeof(struct Node));
  if (newnode == NULL)
    return NULL;

  newnode->below = malloc(sizeof(struct Node *));
  if (newnode->below == NULL)
  {
    free(newnode);
    return NULL;
  }
  newnode->value = value;
  newnode->line = line;
  newnode->column = column;
  return newnode;
}

int main(int argc, char *argv[])
{
  struct Stack *mystack = createstack(NULL);
  struct Node *exnode = createnode('(', 10, 2);
  push(mystack, exnode);
  printstack(mystack);

  printf("len: %ld\n", mystack->lenght);

  struct Node *top = pop(mystack);
  printf("top value: %c\n", top->value);
  printstack(mystack);

  exnode = createnode('[', 10, 2);
  push(mystack, exnode);
  exnode = createnode('(', 10, 2);
  push(mystack, exnode);
  exnode = createnode('*', 10, 2);
  push(mystack, exnode);
  printstack(mystack);

  while ((top = pop(mystack)) != NULL)
  {
    printf("top value: %c\n", top->value);
    printstack(mystack);
    printf("len: %ld\n====================\n", mystack->lenght);
  }
}
