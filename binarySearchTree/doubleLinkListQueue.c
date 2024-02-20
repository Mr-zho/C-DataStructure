#include "doubleLinkListQueue.h"
#include "doubleLinkList.h"

/* 队列初始化 */
int doubleLinkListQueueInit(DoubleLinkListQueue **queue)
{
    return DoubleLinkListInit(queue);
}

/* 队列入队 */
int doubleLinkListQueuePush(DoubleLinkListQueue *queue, ELEMENTTYPE data)
{
    return DoubleLinkListTailInsert(queue, data);
}

/* 队列出队 */
int doubleLinkListQueuePop(DoubleLinkListQueue *queue)
{
    return DoubleLinkListHeadDelete(queue);
}

/* 队列的队头元素 */
int doubleLinkListQueueFront(DoubleLinkListQueue *queue, ELEMENTTYPE *data)
{
    return DoubleLinkListGetHeadPositionData(queue, data);
}

/* 队列的队尾元素 */
int doubleLinkListQueueRear(DoubleLinkListQueue *queue, ELEMENTTYPE *data)
{
    return DoubleLinkListGetTailPositionData(queue, data);
}

/* 队列的元素个数 */
int doubleLinkListQueueGetSize(DoubleLinkListQueue *queue, int *pSize)
{
    return DoubleLinkListGetSize(queue, pSize);
}

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty(DoubleLinkListQueue *queue)
{
    int size = 0;
    DoubleLinkListGetSize(queue, &size);

    return size == 0 ? 1 : 0;
}

/* 队列销毁 */
int doubleLinkListQueueDestroy(DoubleLinkListQueue *queue)
{
    return DoubleLinkListDestroy(queue);
}