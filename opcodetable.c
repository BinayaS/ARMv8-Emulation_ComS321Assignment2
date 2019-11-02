#include <stdio.h>
#include <string.h>
#include "opcode.h"


int searchTable(int opcode){
  int i;
  for(i == 0; i < 37; i++){
    if(opcodeTable[i].opcode == opcode){
      return i;
    }
  }
  return -1;
}
