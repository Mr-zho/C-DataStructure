#include <stdio.h>
#include "balanceBinarySearchTree.h"


#define BUFFER_SIZE 6

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
    #if 0
    BinarySearchTree * tree = NULL;
    binarySearchTreeInit(&tree, comparFuncBasic, printFuncBasic);

    /* 17 6 23 48 5 11 */
    int nums[BUFFER_SIZE] = {17, 6, 23, 48, 5, 11};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        binarySearchTreeInsert(tree, (void *)&nums[idx]);
    }

    int size = 0;
    binarySearchTreeGetSize(tree, &size);
    printf("size:%d\n", size);

    int height = 0;
    binarySearchTreeGetHeight(tree, &height);
    printf("height:%d\n", height);

    /* 层序遍历 */
    binarySearchTreeLevelOrder(tree);
    printf("\n");
    #endif

    
}