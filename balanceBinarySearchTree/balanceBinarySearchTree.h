#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#define ELEMENTTYPE void *

typedef struct BalanceBinarySearchNode
{
    /* 数据域 */
    ELEMENTTYPE data;

    /* 指针域 */
    struct BalanceBinarySearchNode *left;  
    struct BalanceBinarySearchNode *right;
#if 1
    struct BalanceBinarySearchNode * parent;
#endif

    /* 结点的高度 */
    int height;
} BalanceBinarySearchNode;


typedef struct BalanceBinarySearchTree
{
    /* 树的根结点 */
    BalanceBinarySearchNode *root;
    /* 树的元素个数 */
    int size;
    /* 树的高度 */
    int height;

    /* 自定义比较器 */
    int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2);

    /* 自定义打印器 */
    int (*printFunc)(ELEMENTTYPE arg);
} BalanceBinarySearchTree;


/* 树的初始化 */
int balanceBinarySearchTreeInit(BalanceBinarySearchTree **pTree,  int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2), int (*printFunc)(ELEMENTTYPE arg));

/* 树的插入 */
int balanceBinarySearchTreeInsert(BalanceBinarySearchTree *pTree, ELEMENTTYPE data);

/* 树的前序遍历 */
int balanceBinarySearchTreePreOrder(BalanceBinarySearchTree *pTree);

/* 树的中序遍历 */
int balanceBinarySearchTreeInOrder(BalanceBinarySearchTree *pTree);

/* 树的后序遍历 */
int balanceBinarySearchTreePostOrder(BalanceBinarySearchTree *pTree);

/* 树的层序遍历 */
int balanceBinarySearchTreeLevelOrder(BalanceBinarySearchTree *pTree);

/* 树的元素个数 */
int balanceBinarySearchTreeGetSize(BalanceBinarySearchTree *pTree, int *pSize);

/* 树的高度 */
int balanceBinarySearchTreeGetHeight(BalanceBinarySearchTree *pTree, int *pHeight);

/* 树的销毁 */
int balanceBinarySearchTreeDestroy(BalanceBinarySearchTree *pTree);

/* 树的删除 */
int balanceBinarySearchTreeDelete(BalanceBinarySearchTree *pTree, ELEMENTTYPE data);

/* 树是否存在指定元素 */
int balanceBinarySearchTreeIsContainVal(BalanceBinarySearchTree *pTree, ELEMENTTYPE data);

/* 树形打印 */
int balanceBinarySearchTreePrintAsTree(BalanceBinarySearchTree *pTree);
#endif