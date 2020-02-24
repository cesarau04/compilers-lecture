#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

size_t errfound = 0;
struct Stack *mystack;

void rmcomments(char *str, size_t linenum);
void checkbalance(char *str, size_t linenum);

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Error: invalid argument\n");
    return 1;
  }

  char const *const fileName = argv[1];
  FILE *file = fopen(fileName, "r");

  if (file == NULL)
  {
    printf("Error: cannot open file\n");
    return 1;
  }

  char line[256];
  size_t linenum = 1;
  mystack = createstack(NULL);

  while (fgets(line, sizeof(line), file))
  {
    rmcomments(line, linenum);
    checkbalance(line, linenum);
    linenum++;
  }

  if (!isempty(mystack)){
    struct Node* unusednode = pop(mystack);
    while (unusednode->below != NULL){
      printf("\nerror: no closing at (%ld, %ld)\n", unusednode->line, unusednode->column);
      printf("%s\n", unusednode->data);
      for (size_t i = 0; i < unusednode->column; i++)
      {
       printf(" ");
      }
      printf("^\n");
      unusednode = unusednode->below;
      errfound++;
    }
    free(unusednode);
  }

  if (!errfound)
  {
    printf("\nNo errors found!\n");
  }
  else
  {
    printf("\nTotal errors found: %ld\n", errfound);
  }

  fclose(file);
  return 0;
}

void rmcomments(char *str, size_t linenum)
{
  size_t i = 0;
  size_t qoutecounter = 0;
  size_t lastquotecol = 0;
  char c;
  char c_prev;

  while ((c = str[i++]) != '\0')
  {
    if (c == '"')
    {
      qoutecounter++;
      lastquotecol = i - 1;
    }
    if (qoutecounter % 2 != 0)
    { // if quote open
      continue;
    }
    else
    {
      if (c == '/' && c_prev == '/')
      {
        str[i - 2] = '\n';
        str[i - 1] = '\0';
        break;
      }
      c_prev = c;
    }
  }
}

void checkbalance(char *str, size_t linenum)
{
  size_t i = 0;
  char c;

  while ((c = str[i++]) != '\0')
  {
    if (c == '(' || c == '[' || c == '{')
    {
      struct Node *currentnode = createnode(c, linenum, i - 1, str);
      push(mystack, currentnode);
    }
    else if (c == ')')
    {
      struct Node *lastnode = pop(mystack);
      if (lastnode != NULL)
      {
        if (lastnode->value != '(')
        {
          printf("error: no closing parentesis at (%ld, %ld)\n", linenum, i - 1);
          printf("%s\n", str);
          for (size_t j = 0; j < i-1; j++)
          {
            printf(" ");
          }
          printf("^\n");
          errfound++;
        }
      }
      else
      {
        printf("error: no opening parentesis at (%ld, %ld)\n", linenum, i - 1);
        printf("%s\n", str);
        for (size_t j = 0; j < i-1; j++)
        {
          printf(" ");
        }
        printf("^\n");
        errfound++;
      }
      free(lastnode);
    }
    else if (c == ']')
    {
      struct Node *lastnode = pop(mystack);
      if (lastnode != NULL)
      {
        if (lastnode->value != '[')
        {
          printf("error: no closing bracket at (%ld, %ld)\n", linenum, i - 1);
          printf("%s\n", str);
          for (size_t j = 0; j < i-1; j++)
          {
            printf(" ");
          }
          printf("^\n");
          errfound++;
        }
      }
      else
      {
        printf("error: no opening bracket at (%ld, %ld)\n", linenum, i - 1);
        printf("%s\n", str);
        for (size_t j = 0; j < i-1; j++)
        {
          printf(" ");
        }
        printf("^\n");
        errfound++;
      }
      free(lastnode);
    }
    else if (c == '}')
    {
      struct Node *lastnode = pop(mystack);
      if (lastnode != NULL)
      {
        if (lastnode->value != '{')
        {
          printf("error: no closing brace at (%ld, %ld)\n", linenum, i - 1);
          printf("%s\n", str);
          for (size_t j = 0; j < i-1; j++)
          {
            printf(" ");
          }
          printf("^\n");
          errfound++;
        }
      }
      else
      {
        printf("error: no opening brace at (%ld, %ld)\n", linenum, i - 1);
        printf("%s\n", str);
        for (size_t j = 0; j < i-1; j++)
        {
          printf(" ");
        }
        printf("^\n");
        errfound++;
      }
      free(lastnode);
    }
  }
}
