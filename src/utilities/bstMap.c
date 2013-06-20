///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: bstMap.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "bstMap.h"

#define EQUAL   0
#define LESS   -1
#define GREATER 1

tree_entry* createTree(void)
{
  tree_entry* res = malloc(sizeof(tree_entry));
  return (res = NULL);
}

tree_entry* mallocEntry(char* label, u32 addr)
{
  printf("Mallocing entry\n");
  tree_entry* res = malloc(sizeof(tree_entry));
  res->label = malloc(sizeof(char) * strlen(label) + 1);
  strcpy(res->label, label);
  res->memAddr = addr;
  return res;
}

tree_entry* insert(tree_entry** node, char* label, u32 addr)
{
  printf("Inserting label %s at addr %d\n", label, addr);
  // if current node is null then assign to this
  if (*node == NULL) return (*node = mallocEntry(label, addr));
  int cmp = strcmp((*node)->label, label);
  // if equivilant then update current memaddr
  if (!cmp) { (*node)->memAddr = addr; return *node; }
  // if less than the current, then go left
  if (cmp < 0) return insert(&(*node)->left, label, addr);
  // else if more than current, then go right
  return insert(&(*node)->right, label, addr);
}

u32 getAddr(tree_entry* node, char* label)
{
  printf("Trying to get label %s, node is currently null? %d\n", label, node == NULL);
  // if the node is NULL then return 0
  if (node == NULL) return 0;
  int cmp = strcmp(node->label, label);
  switch (strcmp(node->label, label))
  {
    case EQUAL:   return node->memAddr;
    case LESS:    return getAddr(node->left,  label);
    case GREATER: return getAddr(node->right, label);
  }
}