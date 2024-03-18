#include <stdio.h>
#include <string.h>
#include "binaryHeap.h"


int compareFunc(void * arg1, void * arg2)
{
    int val1 = *(int *)arg1;
    int val2 = *(int *)arg2;

    return val1 - val2;
}

int main()
{
    BinaryHeap heap;
    binaryHeapInit(&heap, compareFunc);

    int nums[6] = {23, 54, 7, 16, 3, 41};

    for (int idx = 0; idx < 6; idx++)
    {
        binaryHeapInsert(&heap, &nums[idx]);
    }

    /* 元素个数 */
    int size = 0;
    binaryHeapGetSize(&heap, &size);
    printf("size is %d\n", size);

    /* 堆顶元素 */
    int *topVal = NULL;
    binaryHeapTop(&heap, (void **)&topVal);
    printf("topVal:%d\n", *topVal);

    return 0;
}