#include <stdio.h>
#include <stdlib.h>
//#include "hashtable.h"
#include "opcodetable.h"
//#include "opcodetable.c"
#include "readFile.h"
//#include "decoderStructure.h"

/*
1 = B
2 = R
3 = I
4 = D
5 = CB
6 = IW
7 = JS
*/

OpPair opcodeTable[] = {
<<<<<<< HEAD
   {5, "B", 1},
   {37, "BL", 1}, //End 6 bit opcodes
   {84, "B.cond", 5},
   {180, "CBZ", 5},
   {181, "CBNZ", 5}, //End 8 bit opcodes
   {580, "ADDI", 3},
   {584, "ANDI", 3},
   {712, "ORRI", 3},
   {836, "SUBI", 3},
   {840, "EORI", 3},
   {964, "SUBIS", 3}, //End of 10 bit opcodes
   {448, "STURB", 4},
   {450, "LDURB", 4},
   {960, "STURH", 4},
   {962, "LDURH", 4},
   {1104, "AND", 2},
   {1112, "ADD", 2},
   {1238, "SDIV", 2},
   {1238, "UDIV", 2}, //Fo2 now, all division is unsigned, be careful
   {1240, "MUL", 2},
   {1242, "SMULH", 2},
   {1246, "UMULH", 2},
   {1360, "ORR", 2},
   {1472, "STURW", 4},
   {1476, "LDURSW", 4},
   {1690, "LSR", 2},
   {1691, "LSL", 2},
   {1712, "BR", 2},
   {1616, "EOR", 2},
   {1624, "SUB", 2},
   {1880, "SUBS", 2},
   {1984, "STUR", 4},
   {1986, "LDUR", 4},
   {2044, "PRNL", 7},
   {2045, "PRNT", 7},
   {2046, "DUMP", 7},
   {2047, "HALT", 7} //End 11 bit opcodes
=======
   {5, "B"},
   {37, "BL"}, //End 6 bit opcodes
   {84, "B.cond"},
   {180, "CBZ"},
   {181, "CBNZ"}, //End 8 bit opcodes
   {580, "ADDI"},
   {584, "ANDI"},
   {712, "ORRI"},
   {836, "SUBI"},
   {840, "EORI"},
   {964, "SUBIS"}, //End of 10 bit opcodes
   {448, "STURB"},
   {450, "LDURB"},
   {960, "STURH"},
   {962, "LDURH"},
   {1104, "AND"},
   {1112, "ADD"},
   {1238, "SDIV"},
   {1238, "UDIV"}, //For now, all division is unsigned, be careful
   {1240, "MUL"},
   {1242, "SMULH"},
   {1246, "UMULH"},
   {1360, "ORR"},
   {1472, "STURW"},
   {1476, "LDURSW"},
   {1690, "LSR"},
   {1691, "LSL"},
   {1712, "BR"},
   {1616, "EOR"},
   {1624, "SUB"},
   {1880, "SUBS"},
   {1984, "STUR"},
   {1986, "LDUR"},
   {2044, "PRNL"},
   {2045, "PRNT"},
   {2046, "DUMP"},
   {2047, "HALT"} //End 11 bit opcodes
>>>>>>> parent of 12da59a... add opformat to oppair
};

#define MAX_INSTRUCTION_SIZE 1000000

void decode(unsigned int a) {

  int shiftAmount = 6;
  int shift = 32 - shiftAmount;
  int breakout = 0;
  int foundOpcode = 0;
  int opcodeIndex = -1;

  //TODO compare and find the opcode that is given in a
  while(shiftAmount > 0) {

    //printf("%d\n", a>>shift);

    //search for opcode
    opcodeIndex = searchTable(a>>shift, opcodeTable);
    if(opcodeIndex >= 0){
      printf("shiftAmount: %d -- %d -- %s\n",
              shiftAmount, a>>shift, opcodeTable[opcodeIndex].opname);
      foundOpcode = 1;
      breakout = 1;
    }

    switch(opcodeTable[opcodeIndex].opformat) {
      case 1:
        printf("B");
      break;

      case 2:
        printf("R");
      break;

      case  3:
        printf("I");
      break;

      case  4:
        printf("D");
      break;

      case 5:
        printf("CB");
      break;

      case 6:
        printf("IW");
      break;

      case 7:
        printf("JS");
      break;

      default:
        printf("Didn't find opFormat");
      break;
    }

    //update shiftAmount
    switch(shiftAmount) {
      case 11:
        shiftAmount = -1;
      break;

      case 10:
        shiftAmount = 11;
      break;

      case 9:
        shiftAmount = 10;
      break;

      case 8:
        shiftAmount = 9;
      break;

      case 6:
        shiftAmount = 8;
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
