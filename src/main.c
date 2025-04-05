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
    tree = RbTree_Remove(tree, 1);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 30);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 17);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 10);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 5);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 3);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 4);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 15);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 20);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 16);
    RbTree_Print(tree);
    tree = RbTree_Remove(tree, 18);
    RbTree_Print(tree);

    RbTree* tree2 = nullptr;
    RbTree_Print(tree2);
    tree2 = RbTree_Insert(tree2, 5);
    RbTree_Print(tree2);
    tree2 = RbTree_Insert(tree2, -10);
    RbTree_Print(tree2);
    tree2 = RbTree_Insert(tree2, 20);
    RbTree_Print(tree2);
    tree2 = RbTree_Remove(tree2, 5);
    RbTree_Print(tree2);
    tree2 = RbTree_Remove(tree2, 20);
    RbTree_Print(tree2);
    tree2 = RbTree_Remove(tree2, -10);
    RbTree_Print(tree2);
}
