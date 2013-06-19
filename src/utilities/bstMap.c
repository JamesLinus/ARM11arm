///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: bstMap.c
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

#include "bstMap.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// entry to the binary tree
typedef struct entry
{
  // simple textual label
  char *label;
  // memory address
  u32 memAddr;
  // pointers to left and right
  // structs repsectively
  struct entry *right;
  struct entry *left;
} tree_entry;

// PRE  - Given a valid tree_entry
// POST - Returns the tree depth
int treeDepth(tree_entry *entry)
{
  // if entry's null then tree has terminated
  if (entry == NULL) return 0;
  // else find child depths
  int left  = treeDepth(entry->left);
  int right = treeDepth(entry->right);
  // and return the largest of the two, plus
  // one to account for the current node
  if (left > right)
    return left  + 1;
  else
    return right + 1;
}

// return 0 if left is deeper 1 if right is deeper
// deeper is defined as at least bigger by 2 not 1
// -1 otherwise
// PRE  - Given a two valid tree_entry pointers
// POST - Perform a depth comparison, detecting balance
//        hence range of values is fine
int treeDepthComp(tree_entry *left, tree_entry *right)
{
  int depth = treeDepth(left) - treeDepth(right);
  if      (depth > 1)   return  0;
  else if (depth < -1)  return  1;
  else                  return -1;
}

// PRE  - Given a valid tree_entry pointer
// POST - Returns a left rotated tree_entry
tree_entry *leftRotate(tree_entry *entry)
{
  tree_entry *nodeB = entry->right;
  entry->right = nodeB->left;
  return nodeB->left = entry;
}

// PRE  - Given a valid tree_entry pointer
// POST - Returns a right rotated tree_entry
tree_entry *rightRotate(tree_entry *entry)
{
  tree_entry *nodeB = entry->left;
  entry->left = nodeB->right;
  return nodeB->right = entry;

}

tree_entry *rightLeftRotate(tree_entry *entry)
{
  tree_entry *nodeB = entry->right;
  entry->right = rightRotate(nodeB);
  return leftRotate(entry->right);
}

tree_entry *leftRightRotate(tree_entry *entry)
{
  tree_entry *nodeB = entry->left;
  entry->left = leftRotate(nodeB);
  return rightRotate(entry->left);
}

tree_entry *rebalance(tree_entry *entry)
{
  if (treeDepthComp(entry->left, entry->right) == 1)
    if (treeDepthComp(entry->left, entry->right) == 1)
      return leftRotate(entry);
    else
      return rightLeftRotate(entry);
  else if (treeDepthComp(entry->left, entry->right) == 0)
    if (treeDepthComp(entry->left, entry->right) == 1)
      return leftRightRotate(entry);
    else
      return rightRotate(entry);
  return entry;
}

char *copy(char *str)
{
  char *string = (char *)malloc((strlen(str) + 1) * sizeof(char));
  if (string == NULL)
  {
    perror("malloc in cop() failed (bstMap.c)");
    exit(EXIT_FAILURE);
  }
  return strcpy(string, str);
}

tree_entry *malloc_entry(char *label, uint32_t memAddr)
{
  assert(label != NULL);
  assert(memAddr != 0);
  tree_entry *entry = (tree_entry *)malloc(sizeof(tree_entry));

  if (entry == NULL)
  {
    perror("malloc failed in malloc_entry (btsMap.c)");
    exit(EXIT_FAILURE);
  }

  entry->label = copy(label);
  entry->memAddr = memAddr;
  entry->right = NULL;
  entry->left = NULL;

  return entry;
}

void destroy_tree(tree_entry *root)
{
  free(root->label);
  destroy_tree(root->left);
  destroy_tree(root->right);
  free(root);
}

tree_entry *createTree(void)
{
  return NULL;
}

// TODO: figure out where to call the rebalance function
// I have been looking at it for too long must be easy just cannot see it
tree_entry *insert(tree_entry *root, char *label, uint32_t memAddr)
{
  // if root is null
  if      (root == NULL)
    // then return the newly mem alloced entry
    return mallocEntry(label, memAddr);
  // else if the root 
  else if (!strcmp(root->label, label))
    root->memAddr = memAddr;
  else if (strcmp(root->label, label) < 0)
  {
    if    (root->right == NULL)
      root->right = malloc_entry(label, memAddr);
    else
      insert(root->right, label, memAddr);
  }
  else if (root->left == NULL)
    root->left = malloc_entry(label, memAddr);
  else
    insert(root->right, label, memAddr);

  return root;
}

uint32_t get(tree_entry *root, char *label)
{
  assert(label != NULL);

  // Tree will always contain item looked for

  if (!strcmp(root->label, label))
  {
    return root->memAddr;
  }
  else if (strcmp(root->label, label) < 0)
  {
    return get(root->right, label);
  }
  else
  {
    return get(root->left, label);
  }

}