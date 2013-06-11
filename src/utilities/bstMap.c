#include <stdint.h> 
#include <stdlib.h>
#include <string.h>

typedef struct entry
{
  char* label;
  uint32_t memAddr;
  tree_entry* right;
  tree_entry* left;

} tree_entry;

char* copy(char* str)
{
  char* string = (char*)malloc((strlen(str) + 1) * getsize(char));
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
  return malloc_entry("m", NULL);
}

tree_entry* insert(tree_entry* root, char* label, uint32_t memAddr)
{
  if(!strcmp(root->label, label))
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