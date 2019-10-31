#include <stdio.h>
//#include "hashtable.h"
//#include "opcodetable.h"
#include "readFile.h"
//#include "decoderStructure.h"

#define MAX_ARRAY_SIZE 1000000

int main(int argc, char const *argv[])
{

  char a[100] = "Hi from teletype\n";
  
  int instructionArray[MAX_ARRAY_SIZE] = {-1};
  int counter = 0;

  printf("%s", a);

  //read from file and put all instructions into instructionArray
  counter = readFile(argc, argv, instructionArray);
  
  for(int i = 0; i < counter; i++) {
    printf("%x\n", instructionArray[i]);
  }
  
  //TODO parse command line arguments
  
  //TODO compare opcode by taking the instruction and shifting right till you have just the beggining and compare it to 

  return 0;
};
