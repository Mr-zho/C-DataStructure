#include "binarySearchTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "doubleLinkListQueue.h"
#include "dynamicArrayStack.h"
#include <stdbool.h>

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
/* 当前结点是父结点的左子树 */
static int BalanceBinarySearchTreeNodeIsLeft(BinarySearchNode *node);
/* 当前结点是父结点的右子树 */
static int BalanceBinarySearchTreeNodeIsRight(BinarySearchNode *node);
/* 结点的前驱结点 */
static BinarySearchNode * BinarySearchTreeNodeGetPrecursor(BinarySearchNode *node);
/* 结点的后继结点 */
static BinarySearchNode * BinarySearchTreeNodeGetSuccessor(BinarySearchNode *node);
/* 前序遍历 */
static int binarySearchTreeInnerPreOrder(BinarySearchTree *pTree, BinarySearchNode * travelNode);
/* 中序遍历 */
static int binarySearchTreeInnerInOrder(BinarySearchTree *pTree, BinarySearchNode * travelNode);
/* 后序遍历 */
static int binarySearchTreeInnerPostOrder(BinarySearchTree *pTree, BinarySearchNode * travelNode);
/* 根据指定的值获取对应的结点 */
static BinarySearchNode * baseAppointValGetBSTreeNode(BinarySearchTree *pTree, ELEMENTTYPE data);


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
/* 前驱结点是: 当前结点中序遍历(有序的)的前一个结点 */
static BinarySearchNode * BinarySearchTreeNodeGetPrecursor(BinarySearchNode *node)
{
    BinarySearchNode * travelNode = NULL;
    if (node->left != NULL)
    {
        travelNode = node->left;
        while (travelNode->right != NULL)
        {
            /* node->left->right->right->...... */
            travelNode = travelNode->right;
        }
        return travelNode;
    }

    /* 如果程序执行到这里, 说明: 左子树一定为空 */
    /* 只能够往上面(parent->parent->parent)找 */

    travelNode = node;
    while (travelNode->parent != NULL && travelNode == travelNode->parent->left)
    {
        travelNode = travelNode->parent;
    }
    /* 退出这个循环: case1.travelNode->parent == NULL case2.当前结点是父结点的右边 */
    return travelNode->parent;
}

/* 结点的后继结点 */
/* 后继结点是: 当前结点中序遍历(有序的)的后一个结点 */
static BinarySearchNode * BinarySearchTreeNodeGetSuccessor(BinarySearchNode *node)
{
    BinarySearchNode * travelNode = NULL;
    if (node->right != NULL)
    {
        travelNode = node->right;
        while (travelNode->left != NULL)
        {
            travelNode = travelNode->left;
        }
        return travelNode;
    }

    /* 程序执行到这个地方, 说明: 右子树一定为空 */
    /* 只能够往上面走(parent->parent->parent...)找 */
    travelNode = node;
    while (travelNode->parent != NULL &&  travelNode == travelNode->parent->right)
    {
        travelNode = travelNode->parent;
    }
    /* 退出循环条件: case1.travelNode->parent == NULL case 2. travelNode == node->parent->left */
    return travelNode->parent;
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

/* 当前结点是父结点的左子树 */
static int BinarySearchTreeNodeIsLeft(BinarySearchNode *node)
{
    return (node->parent != NULL) && (node == node->parent->left);
}

/* 当前结点是父结点的右子树 */
static int BinarySearchTreeNodeIsRight(BinarySearchNode *node)
{
    return (node->parent != NULL) && (node == node->parent->right);
}

/* 创建二叉搜索树的结点 */
static BinarySearchNode * createBinarySearchTreeNode(ELEMENTTYPE data, BinarySearchNode * parent)
{
    BinarySearchNode *newNode = (BinarySearchNode *)malloc(sizeof(BinarySearchNode) * 1);
    if (newNode == NULL)
    {
        return NULL;
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
        /* 树的元素个数加一. */
        (pTree->size)++;
        
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

/* 前序遍历 */
static int binarySearchTreeInnerPreOrder(BinarySearchTree *pTree, BinarySearchNode * travelNode)
{
    #if 0
    /* 递归实现 */
    if (travelNode == NULL)
    {
        return ON_SUCCESS;
    }

    /* 根结点 */
    pTree->printFunc(travelNode->data);
    /* 左子树 */
    binarySearchTreeInnerPreOrder(pTree, travelNode->left);
    /* 右子树 */
    binarySearchTreeInnerPreOrder(pTree, travelNode->right);
    #else
    /* 非递归实现 */
    if (travelNode == NULL)
    {
        return ON_SUCCESS;
    }

    DynamicArrayStack stack;

    /* 初始化栈 */
    dynamicArrayStackInit(&stack);

    while (true)
    {
        if (travelNode != NULL)
        {
            /* 访问travelNode结点 */
            pTree->printFunc(travelNode->data);
            /* 将右结点入栈 */
            if (travelNode->right != NULL)
            {
                dynamicArrayStackPush(&stack, travelNode->data);
            }
            /* 向左边走 */
            travelNode = travelNode->left;
        }
        else
        {
            /* 栈是否为空 */
            if (dynamicArrayStackIsEmpty(&stack))
            {
                return ON_SUCCESS;
            }
            else
            {
                dynamicArrayStackTop(&stack, &travelNode);
                dynamicArrayStackPop(&stack);
            }
        }
    }
    
    #endif


    return ON_SUCCESS;
}

/* 树的前序遍历 */
/* 根结点, 左子树, 右子树 */
int binarySearchTreePreOrder(BinarySearchTree *pTree)
{
    if (pTree == NULL)
    {
        return NULL_PTR;
    }

    return binarySearchTreeInnerPreOrder(pTree, pTree->root);
}

/* 树的中序遍历 */
static int binarySearchTreeInnerInOrder(BinarySearchTree *pTree, BinarySearchNode * travelNode)
{
    #if 0
    /* 树的递归实现 */
    if (travelNode == NULL)
    {
        return ON_SUCCESS;
    }

    /* 左子树 */
    binarySearchTreeInnerInOrder(pTree, travelNode->left);
    /* 根结点 */
    pTree->printFunc(travelNode->data);
    /* 右子树 */
    binarySearchTreeInnerInOrder(pTree, travelNode->right);
    #else
    /* 树的非递归实现 */
    DynamicArrayStack stack;

    /* 初始化栈 */
    dynamicArrayStackInit(&stack);


    while (true)
    {
        if (travelNode != NULL)
        {
            dynamicArrayStackPush(&stack, travelNode);
            travelNode = travelNode->left;
        }
        else
        {
            if (dynamicArrayStackIsEmpty(&stack))
            {
                return;
            }
            else
            {
                dynamicArrayStackTop(&stack, &travelNode);
                dynamicArrayStackPop(&stack);

                /* 访问 travelNode结点 */
                pTree->printFunc(travelNode->data);

                /* 让右结点进行中序遍历 */
                travelNode = travelNode->right;
            }
        }
    }
    #endif
    return ON_SUCCESS;
}


/* 树的中序遍历 */
/* 左子树, 根结点, 右子树 */
int binarySearchTreeInOrder(BinarySearchTree *pTree)
{
    if (pTree == NULL)
    {
        return NULL_PTR;
    }

    return binarySearchTreeInnerInOrder(pTree, pTree->root);
}

/* 树的中序遍历 */
static int binarySearchTreeInnerPostOrder(BinarySearchTree *pTree, BinarySearchNode * travelNode)
{
    #if 0
    /* 递归实现 */
    if (travelNode == NULL)
    {
        return ON_SUCCESS;
    }

    /* 左子树 */
    binarySearchTreeInnerPostOrder(pTree, travelNode->left);
    /* 右子树 */
    binarySearchTreeInnerPostOrder(pTree, travelNode->right);
    /* 根结点 */
    pTree->printFunc(travelNode->data);
    #else
    /* 树的非递归实现 */
    DynamicArrayStack stack;

    /* 初始化栈 */
    dynamicArrayStackInit(&stack);
    /* 压栈 */
    dynamicArrayStackPush(&stack, travelNode);
    
    BinarySearchNode * prevVisitNode = NULL;

    BinarySearchNode * topVal = NULL;
    while (!dynamicArrayStackIsEmpty(&stack))
    {
        dynamicArrayStackTop(&stack, &topVal);

        if (BinarySearchTreeNodeIsLeaf(topVal) || (prevVisitNode != NULL && prevVisitNode->parent == topVal))
        {
            dynamicArrayStackTop(&stack, &prevVisitNode);
            /* 访问结点 */
            pTree->printFunc(prevVisitNode->data);
        }
        else
        {
            if (topVal->right != NULL)
            {
                dynamicArrayStackPush(&stack, topVal->right);
            }   

            if (topVal->left != NULL)
            {
                dynamicArrayStackPush(&stack, topVal->left);
            }
        }
    }
    #endif
    return ON_SUCCESS;
}

/* 树的后序遍历 */
/* 左子树, 右子树, 根结点 */
int binarySearchTreePostOrder(BinarySearchTree *pTree)
{
    if (pTree == NULL)
    {
        return NULL_PTR;
    }
    
    return binarySearchTreeInnerPostOrder(pTree, pTree->root);
}

/* 树的层序遍历 */
/* */
int binarySearchTreeLevelOrder(BinarySearchTree *pTree)
{
    if (pTree == NULL)
    {
        return NULL_PTR;
    }

#if 1
    if (pTree->root == NULL)
    {
        return ON_SUCCESS;
    }
#else
    if (pTree->size == 0)
    {
        return ON_SUCCESS;
    }
#endif

    DoubleLinkListQueue *queue = NULL;
    doubleLinkListQueueInit(&queue);

    doubleLinkListQueuePush(queue, pTree->root);

    BinarySearchNode * frontVal = NULL;
    while(!doubleLinkListQueueIsEmpty(queue))
    {
        /* 取出队头元素 */
        doubleLinkListQueueFront(queue, (void **)&frontVal);
        /* 出队 */
        doubleLinkListQueuePop(queue);
        /* 打印器 */
        pTree->printFunc(frontVal->data);

        /* 左子树入队 */
        if (frontVal->left != NULL)
        {
            doubleLinkListQueuePush(queue, frontVal->left);
        }

        /* 右子树入队 */
        if (frontVal->right != NULL)
        {
            doubleLinkListQueuePush(queue, frontVal->right);
        }
    }

    /* 释放队列 */
    doubleLinkListQueueDestroy(queue);

    return ON_SUCCESS;
}

/* 树的高度 */
int binarySearchTreeGetHeight(BinarySearchTree *pTree, int *pHeight)
{
    if (pTree == NULL || pHeight == NULL)
    {
        return NULL_PTR;
    }

    /* 空树 */
    if (pTree->root == NULL)
    {
        /* 解引用 */
        *pHeight = 0;
        return ON_SUCCESS;
    }

    /* 程序到这个地方, 根结点不为NULL. 一定有结点. */

    int height = 0;
    DoubleLinkListQueue *queue = NULL;
    doubleLinkListQueueInit(&queue);

    doubleLinkListQueuePush(queue, pTree->root);
    int levelSize = 1;

    BinarySearchNode * frontVal = NULL;
    while(!doubleLinkListQueueIsEmpty(queue))
    {
        /* 取出队头元素 */
        doubleLinkListQueueFront(queue, (void **)frontVal);
        /* 出队 */
        doubleLinkListQueuePop(queue);

        /* 当前层的结点个数减一 */
        levelSize--;

        /* 左子树入队 */
        if (frontVal->left != NULL)
        {
            doubleLinkListQueuePush(queue, frontVal->left);
        }

        /* 右子树入队 */
        if (frontVal->right != NULL)
        {
            doubleLinkListQueuePush(queue, frontVal->right);
        }

        if (levelSize == 0)
        {
            /* 树的高度加一. */
            height++;
            /* 当前层的结点已经全部结束了 */
            doubleLinkListQueueGetSize(queue, &levelSize);
        }
    }

    /* 释放队列 */
    doubleLinkListQueueDestroy(queue);

    /* 解引用 */
    *pHeight = height;

    return ON_SUCCESS;
}

/* 树的销毁 */
int binarySearchTreeDestroy(BinarySearchTree *pTree)
{
    /* 只需要遍历到所有的结点 & 释放 */
#if 1
    if (pTree == NULL)
    {
        return NULL_PTR;
    }

    if (pTree->root == NULL)
    {
        return ON_SUCCESS;
    }


    DoubleLinkListQueue *queue = NULL;
    doubleLinkListQueueInit(&queue);

    /* 根结点入队 */
    doubleLinkListQueuePush(queue, pTree->root);

    BinarySearchNode * frontVal = NULL;
    while(!doubleLinkListQueueIsEmpty(queue))
    {
        /* 取出队头元素 */
        doubleLinkListQueueFront(queue, (void **)&frontVal);
        /* 出队 */
        doubleLinkListQueuePop(queue);

        /* 左子树入队 */
        if (frontVal->left != NULL)
        {
            doubleLinkListQueuePush(queue, frontVal->left);
        }

        /* 右子树入队 */
        if (frontVal->right != NULL)
        {
            doubleLinkListQueuePush(queue, frontVal->right);
        }

        /* 释放结点 */
        if (frontVal != NULL)
        {
            free(frontVal);
            frontVal = NULL;
        }
    }
    /* 释放队列 */
    doubleLinkListQueueDestroy(queue);

    /* 释放树 */
    if (pTree != NULL)
    {
        free(pTree);
        pTree = NULL;
    }

    return ON_SUCCESS;
#else
    /* 使用中序遍历的方式去释放结点信息 */

#endif
}


/* 树的删除 */
int binarySearchTreeIsContainVal(BinarySearchTree *pTree, ELEMENTTYPE data)
{
    if (pTree == NULL)
    {
        return NULL_PTR;
    }

    return baseAppointValGetBSTreeNode(pTree, data) == NULL ? 0 : 1;
}


static BinarySearchNode * baseAppointValGetBSTreeNode(BinarySearchTree *pTree, ELEMENTTYPE data)
{
    BinarySearchNode * travelNode = pTree->root;
    int cmp = 0;
    while (travelNode != NULL)
    {
        cmp = pTree->compareFunc(data, travelNode->data);
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp == 0)
        {
            return travelNode;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
    }
    /* 退出循环: travelNode == NULL */
    return travelNode;
}

static int binarySearchTreeDeleteNode(BinarySearchTree *pTree, BinarySearchNode * delNode)
{
    int ret = 0;
    if (delNode == NULL)
    {
        return ret;
    }

    /* 度为2 */
    if (BinarySearchTreeNodeHasTwoChildrens(delNode))
    {
        /* 获取当前结点的前驱结点 */
        BinarySearchNode * preNode = BinarySearchTreeNodeGetPrecursor(delNode);
        /* 前驱结点的值 赋值到 度为2的结点 */
        delNode->data = preNode->data;

        delNode = preNode;
    }
    /* 程序到这个地方，要删除的结点要么是度为1 要么是度为0. */

    
    /* 度为1 */
    BinarySearchNode * childNode = delNode->left != NULL ? delNode->left : delNode->right;

    BinarySearchNode * freeNode = NULL;
    if (childNode != NULL)
    {
        /* 度为1 */
        childNode->parent = delNode->parent;

        if (delNode->parent == NULL)
        {
            /* 度为1 且是根结点 */
            pTree->root = childNode;

            freeNode = delNode;
        }
        else
        {
            if (delNode == delNode->parent->left)
            {
                delNode->parent->left = childNode;
            }
            else if (delNode == delNode->parent->right)
            {
                delNode->parent->right = childNode;
            }
            freeNode = delNode;
        }
    }
    else
    {
        if (delNode->parent == NULL)
        {
            /* 度为0 && 根结点 */
            freeNode = delNode;
          
            /* 根结点置为NULL. */
            pTree->root = NULL;
        }
        else
        {
            /* 度为0 */
            if (delNode == delNode->parent->left)
            {
                delNode->parent->left = NULL;
            }
            else if (delNode == delNode->parent->right)
            {
                delNode->parent->right = NULL;
            }
            freeNode = delNode;
        }
    }

    /* 释放堆空间 */
    if (freeNode != NULL)
    {
        free(freeNode);
        freeNode = NULL;
    }

    /* 树的元素个数减一. */
    (pTree->size)--;

    return ret;
}

/* 树是否存在指定元素 */
int binarySearchTreeDelete(BinarySearchTree *pTree, ELEMENTTYPE data)
{
    if (pTree == NULL)
    {
        return NULL_PTR;
    }

#if 0
    BinarySearchNode * delNode = baseAppointValGetBSTreeNode(pTree, data);
    binarySearchTreeDeleteNode(pTree, delNode);
#else
    binarySearchTreeDeleteNode(pTree, baseAppointValGetBSTreeNode(pTree, data));
#endif
    return ON_SUCCESS;
}

/* 树的元素个数 */
int binarySearchTreeGetSize(BinarySearchTree *pTree, int *pSize)
{
    if (pTree == NULL || pSize == NULL)
    {
        return NULL_PTR;
    }
    *pSize = pTree->size;

    return ON_SUCCESS;
}