#include "node.h"
#include <stdlib.h>

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
