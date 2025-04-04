#include <stdio.h>
#include "include/RbTree.h"

int main()
{
    RbTree* tree = RbTree_Create(10);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 5);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 15);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 3);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 1);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 4);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 20);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 30);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 16);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 18);
    RbTree_Print(tree);
    tree = RbTree_Insert(tree, 17);
    RbTree_Print(tree);
}

