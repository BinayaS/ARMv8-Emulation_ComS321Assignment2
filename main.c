#include <stdio.h>
<<<<<<< HEAD
#include "hashtable.h"

=======
#include "readFile.h"
>>>>>>> 7afcf8cc471cdc5e5b528ace84f853ceabe19c2a

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
