#include "binarySearchTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    MALLOC_ERROR,
    NULL_PTR,
    INVALID_ACCESS,
};

/* 静态函数前置声明 */
/* 创建二叉搜索树结点 */
static BinarySearchNode * createBinarySearchTreeNode(ELEMENTTYPE data, BinarySearchNode * parent);

/* 结点的度为2 */
static int BinarySearchTreeNodeHasTwoChildrens(BinarySearchNode *node);
/* 结点的度为1 */
static int BinarySearchTreeNodeHasOneChildrens(BinarySearchNode *node);
/* 结点的度为0 (叶子结点) */
static int BinarySearchTreeNodeIsLeaf(BinarySearchNode *node);
/* 结点的前驱结点 */
static BinarySearchNode * BinarySearchTreeNodeGetPrecursor(BinarySearchNode *node);
/* 结点的后继结点 */
static BinarySearchNode * BinarySearchTreeNodeGetSuccessor(BinarySearchNode *node);


/* 树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pTree, int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2), int (*printFunc)(ELEMENTTYPE arg))
{
    BinarySearchTree * tree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree) * 1);
    if (tree == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(tree, 0, sizeof(BinarySearchTree) * 1);

    /* 树的元素为0. */
    tree->size = 0;
    tree->height = 0;
    tree->root = NULL;

    /* 比较器 */
    tree->compareFunc = compareFunc;

    /* 打印器 */
    tree->printFunc = printFunc;
    
    /* 二级指针解引用 */
    *pTree = tree;
    return ON_SUCCESS;
}

/* 结点的前驱结点 */
static BinarySearchNode * BinarySearchTreeNodeGetPrecursor(BinarySearchNode *node)
{

}

/* 结点的后继结点 */
static BinarySearchNode * BinarySearchTreeNodeGetSuccessor(BinarySearchNode *node)
{
    
}

/* 结点的度为2 */
static int BinarySearchTreeNodeHasTwoChildrens(BinarySearchNode *node)
{
    return node->left != NULL && node->right != NULL;
}

/* 结点的度为1 */
static int BinarySearchTreeNodeHasOneChildrens(BinarySearchNode *node)
{
    return (node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL);
}

/* 结点的度为0 (叶子结点) */
static int BinarySearchTreeNodeIsLeaf(BinarySearchNode *node)
{
    return node->left == NULL && node->right == NULL;
}

/* 创建二叉搜索树的结点 */
static BinarySearchNode * createBinarySearchTreeNode(ELEMENTTYPE data, BinarySearchNode * parent);
{
    BinarySearchNode *newNode = (BinarySearchNode *)malloc(sizeof(BinarySearchNode) * 1);
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;

    return newNode;
}

/* 树的插入 */
int binarySearchTreeInsert(BinarySearchTree *pTree, ELEMENTTYPE data)
{
    /* 判空 */
    if (pTree == NULL)
    {
        return NULL_PTR;
    }

    /* 判断是否为空树 */
#if 0
    if (pTree->size == 0)
    {

    }
#else
    if (pTree->root == NULL)
    {
        pTree->root = createBinarySearchTreeNode(data, NULL);
        if (pTree->root == NULL)
        {
            return MALLOC_ERROR;
        }
        return ON_SUCCESS;
    }
#endif

    /* 程序走到这个地方, 一定不是空树 */
    BinarySearchNode * travelNode = pTree->root;

    BinarySearchNode *parentNode = NULL;
    int cmp = 0;
    while (travelNode != NULL)
    {
        parentNode = travelNode;
        /* 比较器 */
        cmp = pTree->compareFunc(data, travelNode->data);
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp == 0)
        {
            #if 1
            return ON_SUCCESS;
            #else
            travelNode->data = data;
            #endif
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
    }
    /* 程序执行到这里 travelNode一定为NULL. */
    BinarySearchNode *newNode = createBinarySearchTreeNode(data, parentNode);
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }

    if (cmp < 0)
    {
        parentNode->left = newNode;
    }
    else if (cmp > 0)
    {
        parentNode->right = newNode;
    }

    /* 树的元素个数加一. */
    (pTree->size)++;

    return ON_SUCCESS;
}
