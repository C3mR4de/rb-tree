#include "include/RbTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum Color
{
    RED = 0,
    BLACK
};

struct RbTree
{
    int value;
    RbTree* left;
    RbTree* right;
    RbTree* parent;
    enum Color color;
};

static RbTree* RbTree_FallLeft(RbTree* node);
static bool    RbTree_IsLeaf  (RbTree* node);
static bool    RbTree_IsRoot  (RbTree* node);
static bool    RbTree_IsRight (RbTree* node);
static RbTree* RbTree_Next    (RbTree* node);

RbTree* RbTree_Create(int value)
{
    RbTree* root = (RbTree*)malloc(sizeof(RbTree));

    if (root != nullptr)
    {
        *root = (RbTree){value, nullptr, nullptr, nullptr, RED};
    }

    return root;
}

RbTree* RbTree_Search(RbTree* root, int value)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    while (root != nullptr)
    {
        if (value < root->value)
        {
            root = root->left;
        }
        else if (root->value < value)
        {
            root = root->right;
        }
        else
        {
            break;
        }
    }

    return root;
}

RbTree* RbTree_Insert(RbTree* root, int value)
{
    if (root == nullptr)
    {
        return RbTree_Create(value);
    }

    RbTree* node = root;
    bool found = false;

    while (!found)
    {
        if (value < node->value)
        {
            if (node->left == nullptr)
            {
                break;
            }

            node = node->left;
        }
        else if (node->value < value)
        {
            if (node->right == nullptr)
            {
                break;
            }

            node = node->right;
        }
        else
        {
            found = true;
        }
    }

    assert(found == !(value < node->value || node->value < value));

    if (!found)
    {
        RbTree** temp = value < node->value ? &node->left : &node->right;
        *temp = malloc(sizeof(RbTree));
        **temp = (RbTree){value, nullptr, nullptr, node, RED};
    }

    return root;
}

void RbTree_Print(RbTree* root)
{
    for (RbTree* node = RbTree_FallLeft(root); node != nullptr; node = RbTree_Next(node))
    {
        printf("%d ", node->value);
    }

    printf("\n");
}

static RbTree* RbTree_FallLeft(RbTree* node)
{
    assert(node != nullptr);

    while (node->left != nullptr)
    {
        node = node->left;
    }

    return node;
}

static bool RbTree_IsLeaf(RbTree* node)
{
    assert(node != nullptr);
    return node->left == nullptr && node->right == nullptr;
}

static bool RbTree_IsRoot(RbTree* node)
{
    assert(node != nullptr);
    return node->parent == nullptr;
}

static bool RbTree_IsRight(RbTree* node)
{
    assert(node != nullptr && node->parent != nullptr);
    return node == node->parent->right;
}

static RbTree* RbTree_Next(RbTree* node)
{
    assert(node != nullptr);

    if (node->right != nullptr)
    {
        return RbTree_FallLeft(node->right);
    }
    else while (!RbTree_IsRoot(node) && RbTree_IsRight(node))
    {
        node = node->parent;
    }

    return node->parent;
}

