///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: opstructs.h
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

// required for C lexigraphical compilation
typedef void* PtrToBeCast;
typedef void (*Execute)(PtrToBeCast);

typedef struct 
{
  u8 cond;
  Execute function;
  char padding[32];
} BaseInstr;

typedef struct
{
  u8 cond;
  Execute function;
  u8 opcode;
  u32* op1;
  u32* op2;
  u32* des;
} DataProcessingInstr;

typedef struct
{
  u8 cond;
  Execute function;
  u32* cpsr;
  u32* op1;
  u32* op2;
  u32* acc;
  u32* des;
} MultiplyInstr;

typedef struct 
{
  u8 cond;
  Execute function;
  u8 p; u8 u; u8 l;
  u32* rb;
  u32* rd;
  u32* roffset;
} SingleDataInstr;

typedef struct
{
  u8 cond;
  u32 toAdd;
  u32 offset;   // to be signed on execution
  u32* pc;
} BranchInstr;