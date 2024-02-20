#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#define ELEMENTTYPE void *

typedef struct BinarySearchNode
{
    /* 数据域 */
    ELEMENTTYPE data;

    /* 指针域 */
    struct BinarySearchNode *left;  
    struct BinarySearchNode *right;
#if 1
    struct BinarySearchNode * parent;
#endif
} BinarySearchNode;


typedef struct BinarySearchTree
{
    /* 树的根结点 */
    BinarySearchNode *root;
    /* 树的元素个数 */
    int size;
    /* 树的高度 */
    int height;

    /* 自定义比较器 */
    int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2);

    /* 自定义打印器 */
    int (*printFunc)(ELEMENTTYPE arg);
} BinarySearchTree;


/* 树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pTree,  int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2), int (*printFunc)(ELEMENTTYPE arg));

/* 树的插入 */
int binarySearchTreeInsert(BinarySearchTree *pTree, ELEMENTTYPE data);

/* 树的前序遍历 */
int binarySearchTreePreOrder(BinarySearchTree *pTree);

/* 树的中序遍历 */
int binarySearchTreeInOrder(BinarySearchTree *pTree);

/* 树的后序遍历 */
int binarySearchTreePostOrder(BinarySearchTree *pTree);

/* 树的层序遍历 */
int binarySearchTreeLevelOrder(BinarySearchTree *pTree);

/* 树的元素个数 */
int binarySearchTreeGetSize(BinarySearchTree *pTree, int *pSize);

/* 树的高度 */
int binarySearchTreeGetHeight(BinarySearchTree *pTree, int *pHeight);

/* 树的销毁 */
int binarySearchTreeDestroy(BinarySearchTree *pTree);

/* 树的删除 */
int binarySearchTreeDelete(BinarySearchTree *pTree, ELEMENTTYPE data);

/* 树是否存在指定元素 */
int binarySearchTreeIsContainVal(BinarySearchTree *pTree, ELEMENTTYPE data);
#endif