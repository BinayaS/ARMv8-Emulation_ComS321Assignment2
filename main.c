#include <stdio.h>
#include "readFile.h"

struct node {
  char key[100];
  int value;
};

int main(int argc, char const *argv[])
{

  char a[100] = "Hi from teletype\n";

  printf("%s", a);

  readFile(argc, argv);
  
  return 0;
};
