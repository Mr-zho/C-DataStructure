#include <stdio.h>
#include "balanceBinarySearchTree.h"


#define BUFFER_SIZE 10

/* 比较器 */
int comparFuncBasic(void *arg1, void *arg2)
{
    int val1 = *(int *)arg1;
    int val2 = *(int *)arg2;

    return val1 - val2;
}

/* 打印器 */
int printFuncBasic(void *arg)
{
    int ret = 0;
    int val = *(int *)arg;

    printf("val:%d\t", val);
    return ret;
}


int main()
{
    #if 1
    BalanceBinarySearchTree * tree = NULL;
    balanceBinarySearchTreeInit(&tree, comparFuncBasic, printFuncBasic);

    /*  */
    int nums[BUFFER_SIZE] = {13, 14, 15, 12, 11, 17, 16, 8, 9, 1};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        balanceBinarySearchTreeInsert(tree, (void *)&nums[idx]);
    }

    int size = 0;
    balanceBinarySearchTreeGetSize(tree, &size);
    printf("size:%d\n", size);

    int height = 0;
    balanceBinarySearchTreeGetHeight(tree, &height);
    printf("height:%d\n", height);

    /* 层序遍历 */
    balanceBinarySearchTreeLevelOrder(tree);
    printf("\n");
    #endif

    
}