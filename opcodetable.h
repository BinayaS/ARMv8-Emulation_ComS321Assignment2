#ifndef OPCODETABLE_H_
#define OPCODETABLE_H_

typedef struct OpPair {
  char opcode[12];
  char opname[7];
} OpPair;

OpPair opcodeTable[]{
  OpPair{"000101", "B"},
  OpPair{"100101", "BL"}, //End 6 bit opcodes
  OpPair{"01010100", "B.cond"},
  OpPair{"10110100", "CBZ"},
  OpPair{"10110101", "CBNZ"}, //End 8 bit opcodes
  OpPair{"1001000100", "ADDI"},
  OpPair{"1001001000", "ANDI"},
  OpPair{"1011001000", "ORRI"},
  OpPair{"1101000100", "SUBI"},
  OpPair{"1101001000", "EORI"},
  OpPair{"1111000100", "SUBIS"}, //End of 10 bit opcodes
  OpPair{"00111000000", "STURB"},
  OpPair{"00111000010", "LDURB"},
  OpPair{"01111000000", "STURH"},
  OpPair{"01111000010", "LDURH"},
  OpPair{"10001010000", "AND"},
  OpPair{"10001011000", "ADD"},
  OpPair{"10011010110", "SDIV"},
  OpPair{"10011010110", "UDIV"},
  OpPair{"10011011000", "MUL"},
  OpPair{"10011011010", "SMULH"},
  OpPair{"10011011110", "UMULH"},
  OpPair{"10101010000", "ORR"},
  OpPair{"10111000000", "STURW"},
  OpPair{"10111000100", "LDURSW"},
  OpPair{"11010011010", "LSR"},
  OpPair{"11010011011", "LSL"},
  OpPair{"11010110000", "BR"},
  OpPair{"11001010000", "EOR"},
  OpPair{"11001011000", "SUB"},
  OpPair{"11101011000", "SUBS"},
  OpPair{"11111000000", "STUR"},
  OpPair{"11111000010", "LDUR"},
  OpPair{"11111111100", "PRNL"},
  OpPair{"11111111101", "PRNT"},
  OpPair{"11111111110", "DUMP"},
  OpPair{"11111111111", "HALT"} //End 11 bit opcodes
}

#endif // OPCODETABLE_H_
