///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: ass_private.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define REG_D(x) (x << 16)
#define REG_N(x) (x << 12)
#define REG_S(x) (x << 8)
#define REG_M(x) (x << 0)

#define DATA void*
#define KEY char*

typedef struct node node;

uint32_t regToInt(char* reg);
uint8_t arrayContains(char* item, char** array, uint32_t arrayLen);
uint32_t toInt (char* integer);
char** readfile(FILE* file, uint32_t numLines);
uint32_t countLines(FILE* file);
node* makeRBT();
node* get(node* root, KEY key);
void insert(node* root, node* parent, KEY key, DATA data);
uint32_t data_processing(char** expression);
uint32_t multiply_instr(char** line);
uint32_t branch_instr(char** line, node* symbolTable);
uint32_t single_data_transfer(char** line, node* symbolTable);
