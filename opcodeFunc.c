#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include "opcodeFunc.h"
//uint32_t??
u_int8_t memory[4096]; //4096? //1025
u_int8_t stack[512]; //512?? //129
u_int8_t reg[32];

//PC is register 16??? 15??
//SP & FP registers should be initialized to size of stack
/*
void add(int *des, int *reg1, int *reg2); //adds two registers to a destination register
void addI(int *des, int *reg1, int val); //adds a value to a register
void and(int *des, int *reg1, int *reg2);
void andI(int *des, int *reg1, int val);
// FILE *b(int val, *char file, int *pcReg); //32 * number of lines you want to skip
void sub(int *des, int *reg1, int *reg2);
void subI(int *des, int *reg1, int val);
void udiv(int *des, int *reg1, int *reg2);
void sdiv(int *des, int *reg1, int *reg2);
void prnl();
void prnt(int *reg);
// FILE *bl(int val, *char file, int *pcReg, int *blReg);
// FILE *br(*char file, int *reg, int *pcReg);
// FILE *cbz(*char file, int *reg, int val, int *pcReg);
void eor(int *des, int *reg1, int *reg2);
void eorI(int *des, int *reg1, int val);
void mul(int *des, int *reg1, int *reg2);
void orr(int *des, int *reg1, int *reg2);
void orrI(int *des, int *reg1, int val);
void smulh(int *des, int *reg1, int *reg2); //????
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
void umulh(int *des, int *reg1, int *reg2); //???????
void hexdump(FILE *f, int8_t *start, size_t size);
void dump(FILE *f);
char printable_char(uint8_t c);
*/

// int main()
// {
//
//   for(int i = 0; i < 32; i ++)
//   {
//     reg[i] = 0;
//   }
//
//   memory[0] = 10;
//   memory[1] = 12;
//   memory[2] = 46;
//   reg[28] = 512;
//   reg[29] = 512;
//
//   //stur(&reg[0], memory[], &reg[1], 24);
//   //smulh(&reg[1], &reg[2], &reg[3]);
//   //dump(&memory[0], 4096);
//   dump();
//   return 0;
// }


void add(int des, int reg1, int reg2, u_int32_t *regArr)
{
    //*des = *reg1 + *reg2;
    regArr[des] = regArr[reg1] + regArr[reg2];
}

void addI(int des, int reg1, int val, u_int32_t *regArr)
{
    //*des = *reg1 + val;
    regArr[des] = regArr[reg1] + val;
}

void and(int des, int reg1, int reg2, u_int32_t *regArr)
{
    //*des = *reg1 & *reg2;
    regArr[des] = regArr[reg1] & regArr[reg2];
}

void andI(int des, int reg1, int val, u_int32_t *regArr)
{
    //*des = *reg1 & val;
    regArr[des] = regArr[reg1] & val;
}

// FILE *b(int val, *char file, int *pcReg) //test later
// {
//     FILE *f = fopen(*file, "r");
//     for(int i = 0; i < (32 * val); i ++)
//     {
//         fgetc(f);
//     }
//     *pcReg = val;
//     return f;
//
// }

//B.cond

// FILE *bl(int val, *char file, int *pcReg, int *blReg)
// {
//       FILE *f = fopen(*file, "r");
//       for(int i = 0; i < (32 * val); i ++)
//       {
//           fgetc(f);
//       }
//       *blReg = *pcReg + 1;
//       return f;
// }
//
// FILE *br(*char file, int *reg, int *pcReg)
// {
//   FILE *f = fopen(*file, "r");
//   int val = *reg
//   for(int i = 0; i < (32 * val); i ++)
//   {
//       fgetc(f);
//   }
//   *pcReg = val;
//   return f;
// }
//
// FILE *cbz(*char file, int *reg, int val, int *pcReg)
// {
//   FILE *f = fopen(*file, "r");
//   int currReg = *reg
//
//   if(currReg == 0)
//   {
//     for(int i = 0; i < (32 * val); i ++)
//     {
//         fgetc(f);
//     }
//     *pcReg = val;
//   } else
//   {
//       int pc = *pcReg;
//       for(int i = 0; i < (32 * (pc + 1)); i ++)
//       {
//           fgetc(f);
//       }
//       *pcReg = pc + 1;
//   }
//
//   return f;
//
// }
//
// FILE *cbnz(*char file, int *reg, int val, int *pcReg)
// {
//   FILE *f = fopen(*file, "r");
//   int currReg = *reg
//
//   if(currReg != 0)
//   {
//     for(int i = 0; i < (32 * val); i ++)
//     {
//         fgetc(f);
//     }
//     *pcReg = val;
//
//   } else
//   {
//       int pc = *pcReg;
//       for(int i = 0; i < (32 * (pc + 1)); i ++)
//       {
//           fgetc(f);
//       }
//       *pcReg = pc + 1;
//   }
//
//   return f;
//
// }

//DO DUMP
char printable_char(uint8_t c)
{
  return isprint(c) ? c : '.';
}

void hexdump(int8_t *start, size_t size) //displays contents of registers, memory, and disassembled program
{
  size_t i;

  for (i = 0; i < size - (size % 16); i += 16)
  {
    // fprintf(f,
    //         "%08x "
    //         " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
    //         " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
    //         " |%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c|\n",
    //         (int32_t) i,
    //         start[i +  0], start[i +  1], start[i +  2], start[i +  3],
    //         start[i +  4], start[i +  5], start[i +  6], start[i +  7],
    //         start[i +  8], start[i +  9], start[i + 10], start[i + 11],
    //         start[i + 12], start[i + 13], start[i + 14], start[i + 15],
    //         printable_char(start[i +  0]), printable_char(start[i +  1]),
    //         printable_char(start[i +  2]), printable_char(start[i +  3]),
    //         printable_char(start[i +  4]), printable_char(start[i +  5]),
    //         printable_char(start[i +  6]), printable_char(start[i +  7]),
    //         printable_char(start[i +  8]), printable_char(start[i +  9]),
    //         printable_char(start[i + 10]), printable_char(start[i + 11]),
    //         printable_char(start[i + 12]), printable_char(start[i + 13]),
    //         printable_char(start[i + 14]), printable_char(start[i + 15]));

    printf(
                    "%08x "
                    " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
                    " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
                    " |%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c|\n",
                    (int32_t) i,
                    start[i +  0], start[i +  1], start[i +  2], start[i +  3],
                    start[i +  4], start[i +  5], start[i +  6], start[i +  7],
                    start[i +  8], start[i +  9], start[i + 10], start[i + 11],
                    start[i + 12], start[i + 13], start[i + 14], start[i + 15],
                    printable_char(start[i +  0]), printable_char(start[i +  1]),
                    printable_char(start[i +  2]), printable_char(start[i +  3]),
                    printable_char(start[i +  4]), printable_char(start[i +  5]),
                    printable_char(start[i +  6]), printable_char(start[i +  7]),
                    printable_char(start[i +  8]), printable_char(start[i +  9]),
                    printable_char(start[i + 10]), printable_char(start[i + 11]),
                    printable_char(start[i + 12]), printable_char(start[i + 13]),
                    printable_char(start[i + 14]), printable_char(start[i + 15]));
  }
  //fprintf(f, "%08x\n", (int32_t) size);
  printf("%08x\n", (int32_t) size);
}

void dump()
{
    printf("%s\n", "Registers: ");
    for(int i = 0; i < 32; i ++)
    {


        if(i == 16)
        {
            printf("(IPO)  X%d: %d\n", i, reg[i]);

        } else if(i == 17)
        {
            printf("(IP1)  X%d: %d\n", i, reg[i]);

        } else if(i == 28)
        {
            printf(" (SP)  X%d: %d\n", i, reg[i]);
        } else if(i == 29)
        {
            printf(" (FP)  X%d: %d\n", i, reg[i]);
        } else if(i == 30)
        {
            printf(" (LR)  X%d: %d\n", i, reg[i]);
        } else if(i == 31)
        {
            printf("(XZR)  X%d: %d\n", i, reg[i]);
        }
        else if(i < 10)
        {
            printf("       X%d:  %d\n", i, reg[i]);
        } else
        {
            printf("       X%d: %d\n", i, reg[i]);
        }
    }
    prnl();
    prnl();
    //SP & FP - initialized to the size of the stack
    printf("%s\n", "Stack: ");
    hexdump(&stack[0], 512);
    prnl();
    prnl();
    printf("%s\n", "Main Memory: ");
    hexdump(&memory[0], 4096);
}

void eor(int *des, int *reg1, int *reg2, u_int32_t *regArr)
{
    //*des = ~(*reg1 & *reg2) & ~(~(*reg1) & ~(*reg2));
    *des = *reg1 ^ *reg2;
}

void eorI(int *des, int *reg1, int val, u_int32_t *regArr)
{
    //*des = ~(*reg1 & val) & ~(~(*reg1) & ~(val));
    *des = *reg1 ^ val;
}


void halt()
{
    dump();
    exit(0); //terminates
}

void ldur(int des, int reg1, int memory[], int offset, u_int32_t *regArr)
{
    int val = offset / 8; //divides offset by 8
    //*des = memory[val + *reg1]; //loads into des register from the memory array with specified value
    regArr[des] = memory[val + regArr[reg1]];
}


void ldurB(int des, int reg1, int memory[], int offset, u_int32_t *regArr)
{
    int val = offset / 8; //divides offset by 8
    //*des = memory[val + *reg1] & 0x1; //????
    regArr[des] = memory[val + regArr[reg1]] & 0x1;
}


void ldurH(int des, int reg1, int memory[], int offset, u_int32_t *regArr)
{
    int val = offset / 8; //divides offset by 8
    //*des = memory[val + *reg1] & 0xFFFF; //half word representation
    regArr[des] = memory[val + regArr[reg1]] & 0xFFFF;
}


void ldurSW(int des, int reg1, int memory[], int offset, u_int32_t *regArr)
{
    int val = offset / 8; //divides offset by 8
    //*des = memory[val + *reg1] & 0xFFFFFFFF; //in theory, word representation, if a half word --> 0xFFFF a word --> 0xFFFFFFFF
    regArr[des] = memory[val + reg1] & 0xFFFFFFFF;
}

void lsl(int des, int reg1, int offset, u_int32_t *regArr)
{
  // does the offset need to be divded by 8??
  //int val = offset / 8;
  //*des = *reg1 << offset;
  regArr[des] = regArr[reg1] << offset;
}

void lsr(int des, int reg1, int offset, u_int32_t *regArr)
{
    //*des = *reg1 >> offset;
    regArr[des] = regArr[reg1] >> offset;
}

void mul(int des, int reg1, int reg2, u_int32_t *regArr)
{
    //*des = (*reg1) * (*reg2);
    regArr[des] = regArr[reg1]*regArr[reg2];
}

void orr(int des, int reg1, int reg2, u_int32_t *regArr)
{
    //*des = *reg1 | *reg2;
    regArr[des] = regArr[reg1] | regArr[reg2];
}

void orrI(int des, int reg1, int val, u_int32_t *regArr)
{
    //*des = *reg1 | val;
    regArr[des] = regArr[reg1] | val;
}

void prnl()
{
    printf("\n");
}

void prnt(int *reg)
{
    printf("Decimal: %d\nHex: %x\n", *reg, *reg);
}


void sdiv(int des, int reg1, int reg2, u_int32_t *regArr) //??
{
    //*des = *reg1 / *reg2;
    regArr[des] = regArr[reg1] / regArr[reg2];
}

//DO SMULH
void smulh(int des, int reg1, int reg2, u_int32_t *regArr) //???
{
    //*des = (*reg1) * (*reg2);
    regArr[des] = regArr[reg1] * regArr[reg2];
}


void stur(int des, int memory[], int reg, int offset, u_int32_t *regArr)
{
    int val = offset / 8;
    //memory[*reg + val] = *des;
    memory[regArr[reg] + val] = regArr[des];
}


void sturB(int des, int memory[], int reg, int offset, u_int32_t *regArr)
{
    int val = offset / 8;
    //memory[*reg + val] = *des & 0x1;
    memory[regArr[reg] + val] = regArr[des] & 0x1;
}


void sturH(int des, int memory[], int reg, int offset, u_int32_t *regArr)
{
    int val = offset / 8;
    //memory[*reg + val] = *des & 0xFFFF;
    memory[regArr[reg] + val] = regArr[des] & 0xFFFF;
}


void sturW(int des, int memory[], int reg, int offset, u_int32_t *regArr)
{
    int val = offset / 8;
    //memory[*reg + val] = *des & 0xFFFFFFFF;
    memory[regArr[reg] + val] = regArr[des] & 0xFFFFFFFF;
}


void sub(int des, int reg1, int reg2, u_int32_t *regArr)
{
    //*des = *reg1 - *reg2;
    regArr[des] = regArr[reg1] - regArr[reg2];
}

void subI(int des, int reg1, int val, u_int32_t *regArr)
{
    //*des = *reg1 - val;
    regArr[des] = regArr[reg1] - val;
}

//SUBIS - Flag

//SUBS - Flag

void udiv(int des, int reg1, int reg2, u_int32_t *regArr) //??
{
    //*des = *reg1 / *reg2;
    regArr[des] = regArr[reg1]/regArr[reg2];
}

//DO UMULH
void umulh(int des, int reg1, int reg2, u_int32_t *regArr) //???
{
    //*des = (*reg1) * (*reg2);
    regArr[des] = regArr[reg1] * regArr[reg2];
}
