///////////////////////////////////////////////////////////////////////////////
// C Group Project - First Year
// ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// File: bstMap.h
// Group: 21
// Members: amv12, lmj112, skd212
///////////////////////////////////////////////////////////////////////////////

///  STRUCT FOR ENTRY  ////////////////////////////////////////////////////////
typedef struct entry
{
  char* label;   // simple textual label
  u32 memAddr;   // memory address
  struct entry* right;   // pointers to left and right 
  struct entry* left;    // structs repsectively
} tree_entry;

///  TREE CREATION  ///////////////////////////////////////////////////////////
tree_entry* createTree(void);
tree_entry* mallocEntry(char* label, uint32_t memAddr);
void        destroyTree(tree_entry* root);

///  TREE MANIPULATION  ///////////////////////////////////////////////////////
tree_entry* insert(tree_entry* root, char* label, uint32_t memAddr);
tree_entry* leftRotate(tree_entry* entry);
tree_entry* rightRotate(tree_entry* entry);
tree_entry* rightLeftRotate(tree_entry* entry);
tree_entry* leftRightRotate(tree_entry* entry);
tree_entry* rebalance(tree_entry* entry);

///  TREE ANALYSIS  ///////////////////////////////////////////////////////////
uint32_t    get(tree_entry* root, char* label);
int         treeDepth(tree_entry* entry);
int         treeDepthComp(tree_entry* left, tree_entry* right);

///  UTILITIES  ///////////////////////////////////////////////////////////////
char*       copy(char* str);