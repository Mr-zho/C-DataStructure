#ifndef __DOUBLELINKLIST_QUEUE_H__
#define __DOUBLELINKLIST_QUEUE_H__
#include "common.h"

typedef DoubleLinkList DoubleLinkListQueue;

/* 队列初始化 */
int doubleLinkListQueueInit(DoubleLinkListQueue **queue);

/* 队列入队 */
int doubleLinkListQueuePush(DoubleLinkListQueue *queue, ELEMENTTYPE data);

/* 队列出队 */
int doubleLinkListQueuePop(DoubleLinkListQueue *queue);

/* 队列的队头元素 */
int doubleLinkListQueueFront(DoubleLinkListQueue *queue, ELEMENTTYPE *data);

/* 队列的队尾元素 */
int doubleLinkListQueueRear(DoubleLinkListQueue *queue, ELEMENTTYPE *data);

/* 队列的元素个数 */
int doubleLinkListQueueGetSize(DoubleLinkListQueue *queue, int *pSize);

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty(DoubleLinkListQueue *queue);

/* 队列销毁 */
int doubleLinkListQueueDestroy(DoubleLinkListQueue *queue);


#endif // __DOUBLELINKLIST_QUEUE_H__