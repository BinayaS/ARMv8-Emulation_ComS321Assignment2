#include <stdio.h>
//#include "hashtable.h"
//#include "opcodetable.h"
#include "readFile.h"
//#include "decoderStructure.h"

int main(int argc, char const *argv[])
{

  char a[100] = "Hi from teletype\n";

  printf("%s", a);

  readFile(argc, argv);

  return 0;
};
