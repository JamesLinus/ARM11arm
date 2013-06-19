///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: definitions.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef EMULATE_H
#include "../emulate.h"
#endif

#ifndef FLAG_MASKS
#define FLAG_MASKS

#define NO_OF_REGISTERS 13
#define NO_FILE_FOUND    1

#define N_MASK (u32) 1 << 31
#define Z_MASK (u32) 1 << 30
#define C_MASK (u32) 1 << 29
#define V_MASK (u32) 1 << 28

#define N_SET(i) ( ( i & N_MASK ) >> 31 )
#define Z_SET(i) ( ( i & Z_MASK ) >> 30 )
#define C_SET(i) ( ( i & C_MASK ) >> 29 )
#define V_SET(i) ( ( i & V_MASK ) >> 28 )

#define EQ_FLAG 0x00u
#define NE_FLAG 0x01u
#define GE_FLAG 0x0au
#define LT_FLAG 0x0bu
#define GT_FLAG 0x0cu
#define LE_FLAG 0x0du
#define AL_FLAG 0x0eu

#define AND 0x00u
#define EOR 0x01u
#define SUB 0x02u
#define RSB 0x03u
#define ADD 0x04u
#define ADC 0x05u
#define SBC 0x06u
#define RSC 0x07u
#define TST 0x08u
#define TEQ 0x09u
#define CMP 0x0au
#define CMN 0x0bu
#define ORR 0x0cu
#define MOV 0x0du
#define BIC 0x0eu
#define MVN 0x0fu

#define MUL_MASK         0x0fc000f0u
#define DATA_MASK        0x0c000000u
#define BLOCK_DATA_MASK  0x08000000u
#define S_DATA_MASK      0x04000000u
#define BRANCH_MASK      0x0a000000u

#define DATA_TEMPLATE    0x00000000u
#define MUL_TEMPLATE     0x00000090u
#define S_DATA_TEMPLATE  0x04000000u
#define BRANCH_TEMPLATE  0x0a000000u

#define IS_MUL(i)        ((MUL_MASK    & i) == 0x00000090u)
#define IS_DATA(i)       ((DATA_MASK   & i) == 0x00000000u)
#define IS_S_DATA(i)     ((S_DATA_MASK & i) == 0x04000000u)
#define IS_BRANCH(i)     ((BRANCH_MASK & i) == 0x0a000000u)

#define IMMEDIATE_MASK   0x02000000u
#define DATA_OP_MASK     0x01e00000u
#define RN_MASK          0x000f0000u
#define RD_MASK          0x0000f000u
#define RS_MASK          0x00000f00u
#define MUL_RD_MASK      0x000f0000u
#define MUL_RN_MASK      0x0000f000u
#define MUL_RS_MASK      0x00000f00u
#define MUL_RM_MASK      0x0000000fu
#define RM_MASK          0x0000000fu
#define DATA_OPR_2       0x00000fffu
#define BRANCH_OFFSET    0x00ffffffu
#define BRANCH_CTRL      0x00800000u
#define S_DATA_OFFSET    0x00000fffu
#define S_DATA_UP        0x00800000u
#define SET_COND_MASK    0x00100000u
#define ACCUM_MASK       0x00200000u
#define P_INDEX_MASK     0x01000000u
#define LOAD_STORE_MASK  0x00100000u
#define OP_ROTATE        0x00000f00u
#define OP_IMMD          0x000000ffu
#define OP_SHIFT         0x00000ff0u
#define OP_SHIFT_TYPE    0x00000006u
#define SET_FLAGS_S      0x00100000u
#define FIRST_BIT_MASK   0x00000001u

#define MSB 0x80000000u
#define LSL(i,v) (i << v)
#define LSR(i,v) (i >> v)
#define ASR(i,v) (LSR(i,v) | (i & MSB))
#define ROR(i,v) (i >> v) | LSL(i, (0x20u - v))

#define MAX_CHAR_PER_LINE 512
#define MAX_ARG_PER_LINE 5

#define OPCODE_SHIFT(o)    o << 24
#define COND_SHIFT(i)   (u32)(i << 28)
#define SET_SHIFT(i)    (u32)(i << 20)

#define COMPUTES 0
#define SINGLE_OP_ASSIGNS 1
#define SETS_CPSR 2

#define DATA_RD_SHIFT(i) i << 12
#define DATA_RN_SHIFT(i) i << 16

#define REG(i) atoi(i+1)

#define IS_IMMEDIATE(operand) operand[0] == '#'

#endif
