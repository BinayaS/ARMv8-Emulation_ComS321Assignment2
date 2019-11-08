#include <stdio.h>
#include <stdlib.h>
//#include "hashtable.h"
#include "opcodetable.h"
//#include "opcodetable.c"
#include "readFile.h"
//#include "decoderStructure.h"
#include "opcodeFunc.h"

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
   {5, BRANCH, B},
   {37, BL, B}, //End 6 bit opcodes
   {84, BCOND, CB},
   {180, CBZ, CB},
   {181, CBNZ, CB}, //End 8 bit opcodes
   {580, ADDI, I},
   {584, ANDI, I},
   {712, ORRI, I},
   {836, SUBI, I},
   {840, EORI, I},
   {964, SUBIS, I}, //End of 10 bit opcodes
   {448, STURB, D},
   {450, LDURB, D},
   {960, STURH, D},
   {962, LDURH, D},
   {1104, AND, R},
   {1112, ADD, R},
   {1238, SDIV, R},
   {1238, UDIV, R}, //For now, all division is unsigned, be careful
   {1240, MUL, R},
   {1242, SMULH, R},
   {1246, UMULH, R},
   {1360, ORR, R},
   {1472, STURW, D},
   {1476, LDURSW, D},
   {1690, LSR, R},
   {1691, LSL, R},
   {1712, BR, R},
   {1616, EOR, R},
   {1624, SUB, R},
   {1880, SUBS, R},
   {1984, STUR, D},
   {1986, LDUR, D},
   {2044, PRNL, JS},
   {2045, PRNT, JS},
   {2046, DUMP, JS},
   {2047, HALT, JS} //End 11 bit opcodes
};

struct Data {
  int rm, rn, rd, imm, dtaddr, braddr, condbraddr, instructionShift, shamt;
};

#define MAX_INSTRUCTION_SIZE 1000000

struct Data instructionData[MAX_INSTRUCTION_SIZE];
int instructionArray[MAX_INSTRUCTION_SIZE];
u_int32_t regArr[32];
u_int8_t memory[4096];
int counter = 0;

void decode(int a, int i) {

  int shiftAmount = 6;
  int shift = 32 - shiftAmount;
  int breakout = 0;
  int foundOpcode = 0;
  int opcodeIndex = -1;
  int mask = 0x7FF;

  //TODO compare and find the opcode that is given in a
  while(shiftAmount > 0) {

    //printf("%d\n", a>>shift);

    //search for opcode
    //opcodeIndex = searchTable(a>>shift, opcodeTable);

    switch(shiftAmount) {
      case 6:
        mask = 0x3F;
      break;

      case 8:
        mask = 0xFF;
      break;

      case 9:
        mask = 0x1FF;
      break;

      case 10:
        mask = 0x3FF;
      break;

      case 11:
        mask = 0x7FF;
      break;
    }

    opcodeIndex = searchTable(a>>shift & mask, opcodeTable);

    if(opcodeIndex >= 0){
      printf("shiftAmount: %d -- %d -- %d",
              shiftAmount, a>>shift & mask, opcodeTable[opcodeIndex].opname);
      instructionData[i].instructionShift = shift;
      switch(opcodeTable[opcodeIndex].opformat) {
	case R:
    instructionData[i].rd = a & 0x1F;
    instructionData[i].rn = a>>5 & 0x1F;
    instructionData[i].shamt = a>>10 & 0x20;
    instructionData[i].rm = a>>16 & 0x1f;
    printf(" -- R");
    printf(" -> Rm = %d, Rn = %d, Rd = %d\n", instructionData[i].rm, instructionData[i].rn, instructionData[i].rd);
	break;

	case I:
    instructionData[i].rd = a & 0x1F;
    instructionData[i].rn = a>>5 & 0x1F;
    instructionData[i].imm = a>>10 & 0xFFF;
	  printf(" -- I");
	  printf(" -> Imm = %d, Rn = %d, Rd = %d\n", instructionData[i].imm, instructionData[i].rn, instructionData[i].rd);

	break;

	case D:
    instructionData[i].rd = a & 0x1F;
    instructionData[i].rn = a>>5 & 0x1F;
    instructionData[i].dtaddr = a>>12 & 0x7FF;
	  printf(" -- D");
    printf(" -> DTa = %d, Rn = %d, Rt = %d\n", instructionData[i].dtaddr, instructionData[i].rn, instructionData[i].rd);
	break;

	case B:
    instructionData[i].braddr = a & 0x3FFFFFF;
	  printf(" -- B");
    printf(" -> BRa = %d\n", instructionData[i].braddr);
	break;

	case CB:
    instructionData[i].rd = a & 0x1F;
    instructionData[i].condbraddr = a>>5 & 0x7FFFF;
	  printf(" -- CB");
    printf(" -> CondBrA = %d, Rt = %d\n", instructionData[i].condbraddr, instructionData[i].rd);
	break;

	case IW:
	  printf(" -- IW\n");
	break;

	case JS:
	  printf(" -- JS\n");
	break;
      }

      foundOpcode = 1;
      breakout = 1;
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
    printf("Failed to find opcode -->  %x\n", a);
  }

}

void functionCaller() {
  int i;
  unsigned int a;
  for(i = 0; i < counter; i++) {
    a = instructionArray[i];
    switch(a>>instructionData[i].instructionShift) {

      //BRANCH
      case 5:
      break;

      //BL
      case 37:
      break;

      //BCOND
      case 84:
      break;

      //CBZ
      case 180:
      break;

      //ADDI
      case 580:
        addI(instructionData[i].rd, instructionData[i].rn, instructionData[i].imm, regArr);
      break;

      //ANDI
      case 584:
        andI(instructionData[i].rd, instructionData[i].rn, instructionData[i].imm, regArr);
      break;

      //ORRI
      case 712:
        orrI(instructionData[i].rd, instructionData[i].rn, instructionData[i].imm, regArr);
      break;

      //SUBI
      case 836:
        subI(instructionData[i].rd, instructionData[i].rn, instructionData[i].imm, regArr);
      break;

      //EORI
      case 840:
        eorI(instructionData[i].rd, instructionData[i].rn, instructionData[i].imm, regArr);
      break;

      //SUBIS
      case 964:
      break;

      //STURB
      case 448:
        //this is very questionable
        sturB(instructionData[i].rd, memory, instructionData[i].rn, instructionData[i].dtaddr, regArr);
      break;

      //LDURB
      case 450:
        ldurB(instructionData[i].rd, instructionData[i].rn, memory, instructionData[i].dtaddr, regArr);
      break;

      //STURH
      case 960:
        sturH(instructionData[i].rd, memory, instructionData[i].rn, instructionData[i].dtaddr, regArr);
      break;

      //LDURH
      case 962:
        ldurH(instructionData[i].rd, instructionData[i].rn, memory, instructionData[i].dtaddr, regArr);
      break;

      //AND
      case 1104:
        and(instructionData[i].rd, instructionData[i].rn, instructionData[i].rm, regArr);
      break;

      //ADD
      case 1112:
        add(instructionData[i].rd, instructionData[i].rn, instructionData[i].rm, regArr);
      break;

      //UDIV (also SDIV) note: all div. is unsigned
      case 1238:
        udiv(instructionData[i].rd, instructionData[i].rn, instructionData[i].rm, regArr);
      break;

      //MUL
      case 1240:
        mul(instructionData[i].rd, instructionData[i].rn, instructionData[i].rm, regArr);
      break;

      //SMULH
      case 1242:
        smulh(instructionData[i].rd, instructionData[i].rn, instructionData[i].rm, regArr);
      break;

      //UMULH
      case 1246:
        umulh(instructionData[i].rd, instructionData[i].rn, instructionData[i].rm, regArr);
      break;

      //ORR
      case 1360:
        orr(instructionData[i].rd, instructionData[i].rn, instructionData[i].rm, regArr);
      break;

      //STURW
      case 1472:
        sturW(instructionData[i].rd, memory, instructionData[i].rn, instructionData[i].dtaddr, regArr);
      break;

      //LDURSW
      case 1476:
        ldurSW(instructionData[i].rd, instructionData[i].rn, memory, instructionData[i].dtaddr, regArr);
      break;

      //LSR
      case 1690:
        lsr(instructionData[i].rd, instructionData[i].rn, instructionData[i].shamt, regArr);
      break;

      //LSL
      case 1691:
        lsl(instructionData[i].rd, instructionData[i].rn, instructionData[i].shamt, regArr);
      break;

      //BR
      case 1712:
      break;

      //EOR
      case 1616:
        eor(instructionData[i].rd, instructionData[i].rn, instructionData[i].rm, regArr);
      break;

      //SUB
      case 1624:
        sub(instructionData[i].rd, instructionData[i].rn, instructionData[i].rm, regArr);
      break;

      //SUBS
      case 1880:
      break;

      //STUR
      case 1984:
        stur(instructionData[i].rd, memory, instructionData[i].rn, instructionData[i].dtaddr, regArr);
      break;

      //LDUR
      case 1986:
        ldur(instructionData[i].rd, instructionData[i].rn, memory, instructionData[i].dtaddr, regArr);
      break;

      //PRNL
      case 2044:
        prnl();
      break;

      //PRNT
      case 2045:
        //which register is it printing?
        //prnt();
      break;

      //DUMP
      case 2046:
        dump();
      break;

      //HALT
      case 2047:
        halt();
      break;

    }
  }
}


int main(int argc, char const *argv[])
{

  //set local vars.
  int mainMemorySize = 4096;
  int stackSize = 512;

  //TODO???????
  u_int8_t stack[512];


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

  printf("-----\n");

  //TODO compare opcode by taking the instruction and shifting right till you have just the beggining and compare it to the decimal version of the op code
  for(int i = 0; i < counter; i++) {
    //unsigned int a = instructionArray[i];
    int a = instructionArray[i];
    decode(a, i);

    printf("ID -rm: %d -rd:%d -rn:%d\n", instructionData[i].rm, instructionData[i].rd, instructionData[i].rn);

  }

  functionCaller();

  return 0;
};
