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
} BinarySearchTree;


/* 树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pTree,  int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2));

/* 树的插入 */
int binarySearchTreeInsert(BinarySearchTree *pTree, ELEMENTTYPE data);

#endif