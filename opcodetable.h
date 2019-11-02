 #ifndef OPCODETABLE_H_
 #define OPCODETABLE_H_

typedef struct OpPair {
  int opcode;
  char opname[7];
<<<<<<< HEAD
  int opformat;
=======
>>>>>>> parent of 12da59a... add opformat to oppair
} OpPair;

int searchTable(int opcode, OpPair* opcodeTable);

#endif
