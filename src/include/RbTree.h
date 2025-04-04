#ifndef RB_TREE_H

struct RbTree;
typedef struct RbTree RbTree;

RbTree* RbTree_Create(int value);
RbTree* RbTree_Search(RbTree* root, int value);
RbTree* RbTree_Insert(RbTree* root, int value);
RbTree* RbTree_Remove(RbTree* root, int value);
void    RbTree_Print (RbTree* root);

#endif

