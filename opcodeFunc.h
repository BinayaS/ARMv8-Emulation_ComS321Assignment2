#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifndef OPCODEFUNC_H_
#define OPCODEFUNC_H_


void add(int *des, int *reg1, int *reg2);
void addI(int *des, int *reg1, int val);
void and(int *des, int *reg1, int *reg2);
void andI(int *des, int *reg1, int val);
void sub(int *des, int *reg1, int *reg2);
void subI(int *des, int *reg1, int val);
void udiv(int *des, int *reg1, int *reg2);
void sdiv(int *des, int *reg1, int *reg2);
void prnl();
void prnt(int *reg);
void eor(int *des, int *reg1, int *reg2);
void mul(int *des, int *reg1, int *reg2);
void orr(int *des, int *reg1, int *reg2);
void orrI(int *des, int *reg1, int val);
void smulh(int *des, int *reg1, int *reg2);
void ldur(int *des, int *reg1, int memory[], int offset);
void ldurB(int *des, int *reg1, int memory[], int offset);
void ldurH(int *des, int *reg1, int memory[], int offset);
void ldurSW(int *des, int *reg1, int memory[], int offset);
void stur(int *des, int memory[], int *reg, int offset);
void sturB(int *des, int memory[], int *reg, int offset);
void sturH(int *des, int memory[], int *reg, int offset);
void sturW(int *des, int memory[], int *reg, int offset);
void lsl(int *des, int *reg1, int offset);
void lsr(int *des, int *reg1, int offset);
void umulh(int *des, int *reg1, int *reg2);
void dump(FILE *f);
void hexdump(FILE *f, int8_t *start, size_t size);
char printable_char(u_int8_t c);


#endif
