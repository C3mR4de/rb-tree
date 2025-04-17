#include "include/RbTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum Color: bool
{
    RED = false,
    BLACK
};

struct RbTree
{
    RbTree* left;
    RbTree* right;
    RbTree* parent;
    int value;
    enum Color color;
};

static RbTree* RbTree_FallLeft (RbTree* node);
static RbTree* RbTree_FallRight(RbTree* node);

static RbTree* RbTree_RiseLeft  (RbTree* node);
static RbTree* RbTree_RiseRight (RbTree* node);
static RbTree* RbTree_RiseToRoot(RbTree* node);

static RbTree** RbTree_SelfFromLeft  (RbTree* node);
static RbTree** RbTree_SelfFromRight (RbTree* node);
static RbTree** RbTree_SelfFromParent(RbTree* node);

static bool RbTree_HasLeft     (RbTree* node);
static bool RbTree_HasRight    (RbTree* node);
static bool RbTree_HasOnlyLeft (RbTree* node);
static bool RbTree_HasOnlyRight(RbTree* node);

static bool RbTree_Exists (const void* node);
static bool RbTree_IsLeaf (RbTree* node);
static bool RbTree_IsRoot (RbTree* node);
static bool RbTree_IsLeft (RbTree* node);
static bool RbTree_IsRight(RbTree* node);

static RbTree* RbTree_Next(RbTree* node);
static bool    RbTree_FindExact(RbTree* root, int value, RbTree** result);

static void RbTree_SwapPointers      (RbTree** lhs, RbTree** rhs);
// static void RbTree_SwapLeftPointers  (RbTree** lhs, RbTree** rhs);
// static void RbTree_SwapRightPointers (RbTree** lhs, RbTree** rhs);
// static void RbTree_SwapParentPointers(RbTree** lhs, RbTree** rhs);
static void RbTree_SwapNodesInTree   (RbTree** lhs, RbTree** rhs);

RbTree* RbTree_Create(int value)
{
    RbTree* root = (RbTree*)malloc(sizeof(RbTree));

    if (RbTree_Exists(root))
    {
        *root = (RbTree){nullptr, nullptr, nullptr, value, RED};
    }

    return root;
}

RbTree* RbTree_Search(RbTree* root, int value)
{
    if (!RbTree_Exists(root))
    {
        return nullptr;
    }

    while (RbTree_Exists(root))
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
    if (!RbTree_Exists(root))
    {
        return RbTree_Create(value);
    }

    RbTree* node = nullptr;

    if (!RbTree_FindExact(root, value, &node))
    {
        RbTree** temp = value < node->value ? &node->left : &node->right;
        *temp = malloc(sizeof(RbTree));
        **temp = (RbTree){nullptr, nullptr, node, value, RED};
    }

    return root;
}

RbTree* RbTree_Remove(RbTree* root, int value)
{
    if (!RbTree_Exists(root))
    {
        return nullptr;
    }

    RbTree* node = nullptr;

    if (RbTree_FindExact(root, value, &node))
    {
        while (!RbTree_IsLeaf(node))
        {
            RbTree* temp = RbTree_HasLeft(node) ? RbTree_FallRight(node->left) : RbTree_FallLeft(node->right);
            RbTree_SwapNodesInTree(&node, &temp);
        }

        RbTree* node_parent = node->parent;
        RbTree** self_parent = RbTree_SelfFromParent(node);
        free(node);

        if (RbTree_Exists(self_parent))
        {
            *self_parent = nullptr;
            return RbTree_RiseToRoot(node_parent);
        }

        return nullptr;
    }

    return root;
}

void RbTree_Clear(RbTree* root)
{
    while (RbTree_Exists(root))
    {
        root = RbTree_Remove(root, root->value);
    }
}

void RbTree_Print(RbTree* root)
{
    if (!RbTree_Exists(root))
    {
        return;
    }

    for (RbTree* node = RbTree_FallLeft(root); RbTree_Exists(node); node = RbTree_Next(node))
    {
        printf("%d ", node->value);
    }

    printf("\n");
}

static RbTree* RbTree_FallLeft(RbTree* node)
{
    assert(RbTree_Exists(node));

    while (RbTree_HasLeft(node))
    {
        node = node->left;
    }

    return node;
}

static RbTree* RbTree_FallRight(RbTree* node)
{
    assert(RbTree_Exists(node));

    while (RbTree_HasRight(node))
    {
        node = node->right;
    }

    return node;
}

static RbTree* RbTree_RiseLeft(RbTree* node)
{
    assert(RbTree_Exists(node));

    while (!RbTree_IsRoot(node) && RbTree_IsRight(node))
    {
        node = node->parent;
    }

    return node;
}

static RbTree* RbTree_RiseRight(RbTree* node)
{
    assert(RbTree_Exists(node));

    while (!RbTree_IsRoot(node) && RbTree_IsLeft(node))
    {
        node = node->parent;
    }

    return node;
}

static RbTree* RbTree_RiseToRoot(RbTree* node)
{
    assert(RbTree_Exists(node));

    while (!RbTree_IsRoot(node))
    {
        node = node->parent;
    }

    return node;
}

static RbTree** RbTree_SelfFromLeft(RbTree* node)
{
    assert(RbTree_Exists(node));

    if (!RbTree_HasLeft(node))
    {
        return nullptr;
    }

    return &node->left->parent;
}

static RbTree** RbTree_SelfFromRight(RbTree* node)
{
    assert(RbTree_Exists(node));

    if (!RbTree_HasRight(node))
    {
        return nullptr;
    }

    return &node->right->parent;
}

static RbTree** RbTree_SelfFromParent(RbTree* node)
{
    assert(RbTree_Exists(node));

    if (RbTree_IsRoot(node))
    {
        return nullptr;
    }

    return RbTree_IsLeft(node) ? &node->parent->left : &node->parent->right;
}

static bool RbTree_HasLeft(RbTree* node)
{
    assert(RbTree_Exists(node));
    return node->left != nullptr;
}

static bool RbTree_HasRight(RbTree* node)
{
    assert(RbTree_Exists(node));
    return node->right != nullptr;
}

static bool RbTree_HasOnlyLeft(RbTree* node)
{
    assert(RbTree_Exists(node));
    return RbTree_HasLeft(node) && !RbTree_HasRight(node);
}

static bool RbTree_HasOnlyRight(RbTree* node)
{
    assert(RbTree_Exists(node));
    return !RbTree_HasLeft(node) && RbTree_HasRight(node);
}

static bool RbTree_Exists(const void* node)
{
    return node != nullptr;
}

static bool RbTree_IsLeaf(RbTree* node)
{
    assert(RbTree_Exists(node));
    return !(RbTree_HasLeft(node) || RbTree_HasRight(node));
}

static bool RbTree_IsRoot(RbTree* node)
{
    assert(RbTree_Exists(node));
    return node->parent == nullptr;
}

static bool RbTree_IsLeft(RbTree* node)
{
    assert(RbTree_Exists(node));
    assert(RbTree_Exists(node->parent));
    return node == node->parent->left;
}

static bool RbTree_IsRight(RbTree* node)
{
    assert(RbTree_Exists(node));
    assert(RbTree_Exists(node->parent));
    return node == node->parent->right;
}

static RbTree* RbTree_Next(RbTree* node)
{
    assert(RbTree_Exists(node));
    return RbTree_HasRight(node) ? RbTree_FallLeft(node->right) : RbTree_RiseLeft(node)->parent;
}

static bool RbTree_FindExact(RbTree* root, int value, RbTree** result)
{
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
    *result = node;
    return found;
}

static void RbTree_SwapPointers(RbTree** lhs, RbTree** rhs)
{
    assert(RbTree_Exists(lhs));
    assert(RbTree_Exists(rhs));

    RbTree* temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

/*
static void RbTree_SwapLeftPointers(RbTree** lhs, RbTree** rhs)
{
    assert(lhs != nullptr);
    assert(rhs != nullptr);

    RbTree_SwapPointers(&((*lhs)->left), &((*rhs)->left));

    if ((*lhs)->left != nullptr && (*rhs)->left != nullptr)
    {
        (*lhs)->left->parent = *lhs;
        (*rhs)->left->parent = *rhs;
    }
    else if ((*lhs)->left != nullptr && (*rhs)->left == nullptr)
    {
        (*lhs)->left->parent = *lhs;
    }
    else if ((*lhs)->left == nullptr && (*rhs)->left != nullptr)
    {
        (*rhs)->left->parent = *rhs;
    }
}

static void RbTree_SwapRightPointers(RbTree** lhs, RbTree** rhs)
{
    assert(lhs != nullptr);
    assert(rhs != nullptr);

    RbTree_SwapPointers(&((*lhs)->right), &((*rhs)->right));

    if ((*lhs)->right != nullptr && (*rhs)->right != nullptr)
    {
        (*lhs)->right->parent = *lhs;
        (*rhs)->right->parent = *rhs;
    }
    else if ((*lhs)->right != nullptr && (*rhs)->right == nullptr)
    {
        (*lhs)->right->parent = *lhs;
    }
    else if ((*lhs)->right == nullptr && (*rhs)->right != nullptr)
    {
        (*rhs)->right->parent = *rhs;
    }
}

static void RbTree_SwapParentPointers(RbTree** lhs, RbTree** rhs)
{
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    assert(!(RbTree_IsRoot(*lhs) && RbTree_IsRoot(*rhs)));

    bool is_lhs_left = RbTree_IsRoot(*lhs) ? false : RbTree_IsLeft(*lhs);
    bool is_rhs_left = RbTree_IsRoot(*rhs) ? false : RbTree_IsLeft(*rhs);

    RbTree_SwapPointers(&((*lhs)->parent), &((*rhs)->parent));

    if (!(RbTree_IsRoot(*lhs) || RbTree_IsRoot(*rhs)))
    {
        if (is_lhs_left)
        {
            (*lhs)->parent->left = *lhs;
        }
        else
        {
            (*lhs)->parent->right = *lhs;
        }

        if (is_rhs_left)
        {
            (*rhs)->parent->left = *rhs;
        }
        else
        {
            (*rhs)->parent->right = *rhs;
        }
    }
    else if (RbTree_IsRoot(*rhs))
    {
        if (is_lhs_left)
        {
            (*lhs)->parent->left = *lhs;
        }
        else
        {
            (*lhs)->parent->right = *lhs;
        }
    }
    else
    {
        if (is_rhs_left)
        {
            (*rhs)->parent->left = *rhs;
        }
        else
        {
            (*rhs)->parent->right = *rhs;
        }
    }
}
*/

static void RbTree_SwapNodesInTree(RbTree** lhs, RbTree** rhs)
{
    assert(RbTree_Exists(lhs));
    assert(RbTree_Exists(rhs));
    assert(RbTree_Exists(*lhs));
    assert(RbTree_Exists(*rhs));

    /*
    RbTree_SwapLeftPointers(lhs, rhs);
    RbTree_SwapRightPointers(lhs, rhs);
    RbTree_SwapParentPointers(lhs, rhs);
    */

    int temp = (*lhs)->value;
    (*lhs)->value = (*rhs)->value;
    (*rhs)->value = temp;

    RbTree_SwapPointers(lhs, rhs);
}

