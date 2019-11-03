 #ifndef OPCODETABLE_H_
 #define OPCODETABLE_H_

enum EnumOpFormat {
  DEFAULT,
  R,
  I,
  D,
  B,
  CB,
  IW,
  JS
};


typedef struct OpPair {
  int opcode;
  char opname[7];
  enum EnumOpFormat opformat;
} OpPair;

int searchTable(int opcode, OpPair* opcodeTable);

#endif
