 #ifndef OPCODETABLE_H_
 #define OPCODETABLE_H_

typedef struct OpPair {
  int opcode;
  char opname[7];
  char opformat[3];
} OpPair;

int searchTable(int opcode, OpPair* opcodeTable);

#endif
