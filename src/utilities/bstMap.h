///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: bstMap.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#ifndef BST_MAP
#define BST_MAP

#include "../res/uints.h"

///  STRUCT FOR ENTRY  ////////////////////////////////////////////////////////
typedef struct tree_entry tree_entry;

struct tree_entry
{
  char* label;   // simple textual label
  u32 memAddr;   // memory address
  tree_entry* right;   // pointers to left and right 
  tree_entry* left;    // structs repsectively
};

tree_entry* createTree(void);
tree_entry* mallocEntry(char* label, u32 addr);
tree_entry* insert(tree_entry** node, char* label, u32 addr);
u32 getAddr(tree_entry* node, char* label);

#endif
