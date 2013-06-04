///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: definitions.h
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#define NO_OF_REGISTERS 12
#define NO_FILE_FOUND    1

#define N_MASK (u32) 31 << 1
#define Z_MASK (u32) 30 << 1
#define C_MASK (u32) 29 << 1
#define V_MASK (u32) 28 << 1

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

#define IS_MUL(i)        ((MUL_MASK    & i) == 0x00000090u)
#define IS_DATA(i)       ((DATA_MASK   & i) == 0x00000000u)
#define IS_S_DATA(i)     ((S_DATA_MASK & i) == 0x04000000u)
#define IS_BRANCH(i)     ((BRANCH_MASK & i) == 0x0a000000u)
// #define IS_BLOCK_DATA(i) 

#define IMMEDIATE_MASK   0x02000000u
#define DATA_OP_MASK     0x01e00000u
#define RN_MASK          0x000f0000u
#define RD_MASK          0x0000f000u
#define RS_MASK          0x00000f00u
#define RM_MASK          0x0000000fu
#define DATA_OPR_2       0x00000fffu
#define DATA_OP2_ROTATE  0x00000f00u
#define DATA_OP2_IMM     0x000000ffu
#define DATA_OP2_SHIFT   0x00000060u
#define DATA_OP2_CTRL    0x00000010u
#define DATA_OP2_INT     0x00000f80u
#define BRANCH_OFFSET    0x003fffffu
#define BRANCH_CTRL      0x00800000u
#define S_DATA_OFFSET    0x00000fffu
#define S_DATA_UP        0x00800000u
#define SET_COND_MASK    0x00100000u
#define ACCUM_MASK       0x00000100u
#define P_INDEX_MASK     0x01000000u
#define LOAD_STORE_MASK  0x00100000u
#define OP_ROTATE        0x00000f00u
#define OP_IMMD          0x0000000fu
#define OP_SHIFT         0x00000ff0u
#define OP_SHIFT_TYPE    0x00000006u

#define MSB 0x80000000u
#define LSL(i,v) (v << i)
#define LSR(i,v) (i >> v)
#define ASR(i,v) (LSR(i,v) | (i & MSB))
#define ROR(i,v) (i >> v) | (i << (0x20u - v))

#define J_DATA      0x00u
#define J_S_DATA    0x01u
#define J_MUL       0x02u
#define J_BRANCH    0x03u

// Set up program state as a C Struct
typedef struct
{
  u32 e[MEMSIZE];
  u32 d[MEMSIZE];
} Memory;

typedef struct
{
  u32 *r;        // registers
  u32 sp;        // R[13] <- stack pointer
  u32 lr;        // R[14] <- link register
  u32 pc;        // R[15] <- program counter
  u32 cpsr;      // R[16] <- flags
  u32 *em;           // encoded memory
  BaseInstr *dm;       // decoded memory
} Arm;
