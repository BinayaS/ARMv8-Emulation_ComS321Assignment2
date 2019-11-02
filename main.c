#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
//#include "opcodetable.h"
#include "readFile.h"
//#include "decoderStructure.h"

#define MAX_INSTRUCTION_SIZE 1000000

void decode(unsigned int a) {

  int shiftAmount = 11;
  int shift = 32 - shiftAmount;
  int breakout = 0;
  int foundOpcode = 0;
  
  //TODO compare and find the opcode that is given in a
  while(shiftAmount > 0) {
  
    //printf("%d\n", a>>shift);
  
    //search for opcode
    switch(a>>shift) {
      //ADDI
      case (int)580 :
        printf("shiftAmount: %d -- %d -- ADDI\n", shiftAmount, a>>shift);
        foundOpcode = 1;
      break;
      
      //STUR
      case (int)1984 :
        printf("shiftAmount: %d -- %d -- STUR\n", shiftAmount, a>>shift);
        foundOpcode = 1;
      break;
    }
    
    //update shiftAmount
    switch(shiftAmount) {
      case 11:
        shiftAmount = 10;
      break;
      
      case 10:
        shiftAmount = 9;
      break;
      
      case 9:
        shiftAmount = 8;
      break;
      
      case 8:
        shiftAmount = 6;
      break;
      
      case 6:
        shiftAmount = -1;
      break;
    }
    
    //exit while loop
    if(breakout == 1) {
      break;
    }
    
    //update shift
    shift = 32 - shiftAmount;
  }
  
  if(foundOpcode == 0) {
    printf("Failed to find opcode\n");
  }
  
}

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
  
  //TODO compare opcode by taking the instruction and shifting right till you have just the beggining and compare it to the decimal version of the op code
  for(int i = 0; i < counter; i++) {
    unsigned int a = instructionArray[i];
    
    decode(a);
    
    /*
    int shift10 = 32-10;
    int shift11 = 32-11;
    int ADDI = 580;
    int STUR = 1984;
    printf("shift10 decimal: %d -- shift11 decimal: %d -- ", a>>shift10, a>>shift11);
    
    
    if(STUR == a>>shift11) {
      printf("hex: %x ", a);
      printf("MATCH!\n");
    }  else {
      printf("hex: %x\n", a);
    }
    */
  }
  
  

  return 0;
};
