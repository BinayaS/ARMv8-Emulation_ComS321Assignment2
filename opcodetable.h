#ifndef OPCODETABLE_H_
#define OPCODETABLE_H_

typedef struct OpPair {
  int opcode;
  char opname[7];
} OpPair;

OpPair opcodeTable[]{
  OpPair{5, "B"},
  OpPair{37, "BL"}, //End 6 bit opcodes
  OpPair{84, "B.cond"},
  OpPair{180, "CBZ"},
  OpPair{181, "CBNZ"}, //End 8 bit opcodes
  OpPair{580, "ADDI"},
  OpPair{584, "ANDI"},
  OpPair{712, "ORRI"},
  OpPair{836, "SUBI"},
  OpPair{840, "EORI"},
  OpPair{964, "SUBIS"}, //End of 10 bit opcodes
  OpPair{448, "STURB"},
  OpPair{450, "LDURB"},
  OpPair{960, "STURH"},
  OpPair{962, "LDURH"},
  OpPair{1104, "AND"},
  OpPair{1112, "ADD"},
  OpPair{1238, "SDIV"},
  OpPair{1238, "UDIV"}, //For now, all division is unsigned, be careful
  OpPair{1240, "MUL"},
  OpPair{1242, "SMULH"},
  OpPair{1246, "UMULH"},
  OpPair{1360, "ORR"},
  OpPair{1472, "STURW"},
  OpPair{1476, "LDURSW"},
  OpPair{1690, "LSR"},
  OpPair{1691, "LSL"},
  OpPair{1712, "BR"},
  OpPair{1616, "EOR"},
  OpPair{1624, "SUB"},
  OpPair{1880, "SUBS"},
  OpPair{1984, "STUR"},
  OpPair{1986, "LDUR"},
  OpPair{2044, "PRNL"},
  OpPair{2045, "PRNT"},
  OpPair{2046, "DUMP"},
  OpPair{2047, "HALT"} //End 11 bit opcodes
}

int searchTable(int opcode);
#endif // OPCODETABLE_H_
