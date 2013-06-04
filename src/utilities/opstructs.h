///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: opstructs.h
// Group: 21
// Memebers: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

typedef struct 
{
  u8 jump;
  char padding[64];
} BaseOpInstr;

typedef struct 
{
  u8 jump;
  u8 cond;
  u8 immd;
  u8 opcode;
  u8 setcond;
  u32 *rn;
  u32 *rd;
  u16 operand2;
} DataInstr;

typedef struct
{
  u8 jump;
  u8 cond;
  u8 accum;
  u8 setcond;
  u32 *rd;
  u32 *rn;
  u32 *rs;
  u32 *rm;
} MulInstr;

typedef struct
{
  u8 jump;
  u8 cond;
  u8 immd;
  u8 pindex;
  u8 up;
  u8 ls;
  u32 *rn;
  u32 *rd;
  u16 offset;
} SingleDataInstr;

typedef struct
{
  u8 jump;
  u8 cond;
  u32 offset;
} BranchInstr;