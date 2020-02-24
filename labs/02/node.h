#include <stdio.h>

// Base struct inside a stack
struct Node
{
  struct Node *below;
  char value;
  size_t line;
  size_t column;
};

// Creates a node
struct Node *createnode(char value, size_t line, size_t column);