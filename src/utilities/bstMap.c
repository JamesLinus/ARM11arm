#include <stdint.h> 
#include <stdlib.h>
#include <string.h>

typedef struct entry
{
  char* label;
  uint32_t memAddr;
  struct entry* right;
  struct entry* left;

} tree_entry;

int treeDepth(tree_entry* entry) {
  if(entry == NULL)
  {
    return 0;
  }
  int left = treeDepth(entry->left);
  int right = treeDepth(entry->right);
  if(left > right)
  { 
    return left + 1; 
  } else
  {
    return right + 1;
  }
}

// return 0 if left is deeper 1 if right is deeper 
// deeper is defined as at least bigger by 2 not 1
// -1 otherwise
int treeDepthComp(tree_entry* left, tree_entry* right)
{
  int depth = treeDepth(left) - treeDepth(right);
  if(depth > 1)
  {
    return 0;
  } else if(depth < -1)
  {
    return 1;
  } else
  {
    return -1;
  }
}

tree_entry* leftRotate(tree_entry* entry)
{
  tree_entry* nodeB = entry->right;
  entry->right = nodeB->left;
  return nodeB->left = entry;
}

tree_entry* rightRotate(tree_entry* entry)
{
  tree_entry* nodeB = entry->left;
  entry->left = nodeB->right;
  return nodeB->right = entry;

}

tree_entry* rightLeftRotate(tree_entry* entry)
{
  tree_entry* nodeB = entry->right;
  entry->right = rightRotate(nodeB);
  return leftRotate(entry->right);
}

tree_entry* leftRightRotate(tree_entry* entry)
{
  tree_entry* nodeB = entry->left;
  entry->left = leftRotate(nodeB);
  return rightRotate(entry->left);
}

tree_entry* rebalance(tree_entry* entry)
{
  if(treeDepthComp(entry->left, entry->right) == 1)
  {
      if(treeDepthComp(entry->left, entry->right) == 1)
      {
        return leftRotate(entry);
      } else 
      {
        return rightLeftRotate(entry);
      }
  } else if(treeDepthComp(entry->left, entry->right) == 0)
  {
      if(treeDepthComp(entry->left, entry->right) == 1)
      {
        return leftRightRotate(entry);
      } else 
      {
        return rightRotate(entry);
      }
  } 
  return entry;
}

char* copy(char* str)
{
  char* string = (char*)malloc((strlen(str) + 1) * sizeof(char));
  if(string == NULL)
  {
    perror("malloc in cop() failed (bstMap.c)");
    exit(EXIT_FAILURE);
  }
  return strcpy(string, str);
}

tree_entry* malloc_entry(char* label, uint32_t memAddr)
{
  assert(label != NULL);
  assert(memAddr != 0);
  tree_entry* entry = (tree_entry*)malloc(sizeof(tree_entry));

  if(entry == NULL)
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

void destroy_tree(tree_entry* root)
{
  free(root->label);
  destroy_tree(root->left);
  destroy_tree(root->right);
  free(root);
}

tree_entry* createTree(void)
{ 
  return NULL;
}

// TODO: figure out where to call the rebalance function 
// I have been looking at it for too long must be easy just cannot see it
tree_entry* insert(tree_entry* root, char* label, uint32_t memAddr)
{
  
  if(root == NULL)
  {
    return malloc_entry(label, memAddr);
  }
  else if(!strcmp(root->label, label))
  {
    root->memAddr = memAddr;
  } else if(strcmp(root->label, label) < 0)
  {
    if(root->right == NULL)
    {
      root->right = malloc_entry(label, memAddr);
    } else
    {
      insert(root->right, label, memAddr);
    }
  } else
  {
    if(root->left == NULL)
    {
      root->left = malloc_entry(label, memAddr);
    } else
    {
      insert(root->right, label, memAddr);
    }
  }

  return root;
}

uint32_t get(tree_entry* root, char* label)
{
  assert(label != NULL);

  // Tree will always contain item looked for

  if(!strcmp(root->label, label))
  {
    return root->memAddr;
  } else if(strcmp(root->label, label) < 0)
  {
    return get(root->right, label);
  } else
  {
    return get(root->left, label);
  }

}

int main(void)
{
  return 0;
}