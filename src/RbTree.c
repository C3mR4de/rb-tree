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

static RbTree* RbTree_FallLeft  (RbTree* node);
static RbTree* RbTree_FallRight (RbTree* node);
static RbTree* RbTree_RiseLeft  (RbTree* node);
static RbTree* RbTree_RiseRight (RbTree* node);
static RbTree* RbTree_RiseToRoot(RbTree* node);

static bool RbTree_HasLeft (RbTree* node);
static bool RbTree_HasRight(RbTree* node);

static bool RbTree_IsLeaf (RbTree* node);
static bool RbTree_IsRoot (RbTree* node);
static bool RbTree_IsLeft (RbTree* node);
static bool RbTree_IsRight(RbTree* node);

static RbTree* RbTree_Next(RbTree* node);

static void RbTree_SwapPointers(RbTree** lhs, RbTree** rhs);
static void RbTree_SwapNodesInTree(RbTree** lhs, RbTree** rhs);

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
            if (!RbTree_HasLeft(node))
            {
                break;
            }

            node = node->left;
        }
        else if (node->value < value)
        {
            if (!RbTree_HasRight(node))
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

RbTree* RbTree_Remove(RbTree* root, int value)
{
    if (root == nullptr)
    {
        return nullptr;
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

    if (found)
    {
        while (!RbTree_IsLeaf(node))
        {
            if (RbTree_HasLeft(node))
            {
                node = RbTree_FallRight(node->left);
                RbTree* temp = RbTree_RiseLeft(node)->parent;
                RbTree_SwapNodesInTree(&node, &temp);
                node = temp;
            }
            else
            {
                node = RbTree_FallLeft(node->right);
                RbTree* temp = RbTree_RiseRight(node)->parent;
                RbTree_SwapNodesInTree(&node, &temp);
                node = temp;
            }
        }

        RbTree* node_parent = node->parent;

        if (RbTree_IsLeft(node))
        {
            node_parent->left = nullptr;
        }
        else
        {
            node_parent->right = nullptr;
        }

        free(node);
        return RbTree_RiseToRoot(node_parent);
    }

    return root;
}

void RbTree_Print(RbTree* root)
{
    assert(root != nullptr);

    for (RbTree* node = RbTree_FallLeft(root); node != nullptr; node = RbTree_Next(node))
    {
        printf("%d ", node->value);
    }

    printf("\n");
}

static RbTree* RbTree_FallLeft(RbTree* node)
{
    assert(node != nullptr);

    while (RbTree_HasLeft(node))
    {
        node = node->left;
    }

    return node;
}

static RbTree* RbTree_FallRight(RbTree* node)
{
    assert(node != nullptr);

    while (RbTree_HasRight(node))
    {
        node = node->right;
    }

    return node;
}

static RbTree* RbTree_RiseLeft(RbTree* node)
{
    assert(node != nullptr);

    while (!RbTree_IsRoot(node) && RbTree_IsRight(node))
    {
        node = node->parent;
    }

    return node;
}

static RbTree* RbTree_RiseRight(RbTree* node)
{
    assert(node != nullptr);

    while (!RbTree_IsRoot(node) && RbTree_IsLeft(node))
    {
        node = node->parent;
    }

    return node;
}

static RbTree* RbTree_RiseToRoot(RbTree* node)
{
    assert(node != nullptr);

    while (!RbTree_IsRoot(node))
    {
        node = node->parent;
    }

    return node;
}

static bool RbTree_HasLeft(RbTree* node)
{
    assert(node != nullptr);
    return node->left != nullptr;
}

static bool RbTree_HasRight(RbTree* node)
{
    assert(node != nullptr);
    return node->right != nullptr;
}

static bool RbTree_IsLeaf(RbTree* node)
{
    assert(node != nullptr);
    return !(RbTree_HasLeft(node) || RbTree_HasRight(node));
}

static bool RbTree_IsRoot(RbTree* node)
{
    assert(node != nullptr);
    return node->parent == nullptr;
}

static bool RbTree_IsLeft(RbTree* node)
{
    assert(node != nullptr);
    assert(node->parent != nullptr);
    return node == node->parent->left;
}

static bool RbTree_IsRight(RbTree* node)
{
    assert(node != nullptr);
    assert(node->parent != nullptr);
    return node == node->parent->right;
}

static RbTree* RbTree_Next(RbTree* node)
{
    assert(node != nullptr);
    return RbTree_HasRight(node) ? RbTree_FallLeft(node->right) : RbTree_RiseLeft(node)->parent;
}

static void RbTree_SwapPointers(RbTree** lhs, RbTree** rhs)
{
    assert(lhs != nullptr);
    assert(rhs != nullptr);

    RbTree* temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

static void RbTree_SwapNodesInTree(RbTree** lhs, RbTree** rhs)
{
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    assert(*lhs != nullptr);
    assert(*rhs != nullptr);

    RbTree_SwapPointers(&((*lhs)->left), &((*rhs)->left));
    RbTree_SwapPointers(&((*lhs)->right), &((*rhs)->right));
    RbTree_SwapPointers(&((*lhs)->parent), &((*rhs)->parent));
}

