#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

    srand(time(nullptr));

    constexpr size_t max_array_size = 200;
    constexpr size_t max_value = 1000;

    const size_t test_array_size = rand() % max_array_size + 1;
    int* const test_array = malloc(test_array_size * sizeof(int));

    for (size_t i = 0; i < test_array_size; ++i)
    {
        test_array[i] = rand() % (max_value + 1) - (max_value / 2);
    }

    RbTree* test_tree = nullptr;

    for (size_t i = 0; i < test_array_size; ++i)
    {
        test_tree = RbTree_Insert(test_tree, test_array[i]);
        test_tree = RbTree_Insert(test_tree, test_array[i]);
        RbTree_Print(test_tree);
    }

    for (size_t i = test_array_size - 1; i > 0; --i)
    {
        const volatile size_t rand_index = rand();
        const int temp = test_array[i];
        test_array[i] = test_array[rand_index % (i + 1)];
        test_array[rand_index % (i + 1)] = temp;
    }

    for (size_t i = 0; i < test_array_size; ++i)
    {
        test_tree = RbTree_Remove(test_tree, test_array[i]);
        test_tree = RbTree_Remove(test_tree, test_array[i]);
        RbTree_Print(test_tree);
    }

    free(test_array);
}
