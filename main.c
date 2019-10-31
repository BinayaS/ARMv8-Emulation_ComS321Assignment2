#include <stdio.h>
#include <stdlib.h>
//#include "hashtable.h"
//#include "opcodetable.h"
#include "readFile.h"
//#include "decoderStructure.h"

#define MAX_INSTRUCTION_SIZE 1000000

int main(int argc, char const *argv[])
{

  //set local vars.
  int mainMemorySize = 4096;
  int stackSize = 512;
  int instructionArray[MAX_INSTRUCTION_SIZE] = {-1};
  int counter = 0;


  //parse command line arguments if there are two or more arguments
  if(argc >= 2) {
    printf("The arguments supplied are:\n");

    //print out all arguments
    for(int i = 1; i < argc; i++) {
        printf("%s\t ", argv[i]);
    }
    
    printf("\n");
    
    //if atleast three arguments set mainMemorySize
    if(argc >= 3) {
      mainMemorySize = atoi(argv[2]);
      printf("mainMemorySize = %d\n", mainMemorySize);
    }
    
    //if atleas four arguments set stackSize
    if(argc >= 4) {
      stackSize = atoi(argv[3]);
      printf("stackSize = %d\n", stackSize);
    }
    
    //if there is not two or more arguments then print the input format
  } else {
      printf("<.machine file> [-m <main memory size>] [-s <stack size>]\n");
      return 0;
  }

  //read from file and put all instructions into instructionArray
  counter = readFile(argc, argv, instructionArray);
  
  //for visual purposes print out the instructions in hex
  for(int i = 0; i < counter; i++) {
    printf("%x\n", instructionArray[i]);
  }
  
  //TODO compare opcode by taking the instruction and shifting right till you have just the beggining and compare it to 
  

  return 0;
};
