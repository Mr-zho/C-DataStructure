#include <stdio.h>
#include "doubleLinkListQueue.h"

#define BUFFER_SIZE 5

int main()
{
    /* 队列初始化 */
    DoubleLinkListQueue *queue = NULL;
    doubleLinkListQueueInit(&queue);
    
    int nums[BUFFER_SIZE] = {11, 22, 33, 44, 55};
    /* 入队 */
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        doubleLinkListQueuePush(queue, (void *)&nums[idx]);
    }

    int size = 0;
    doubleLinkListQueueGetSize(queue, &size);
    printf("size = %d\n", size);

    /* 队列非空 */
    int *frontValue = NULL;
    while (!doubleLinkListQueueIsEmpty(queue))
    {
        doubleLinkListQueueFront(queue, (void *)&frontValue);
        /* 出队 */
        doubleLinkListQueuePop(queue);

        printf("frontValue:%d\n", *frontValue);
    }

    /* 释放队列 */
    doubleLinkListQueueDestroy(queue);

    return 0;
}