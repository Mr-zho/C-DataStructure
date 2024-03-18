#ifndef _BINARY_HEAP_H__
#define _BINARY_HEAP_H__
#include <stdbool.h>

#define ELEMENT_TYPE void *
typedef struct BinaryHeap
{
    ELEMENT_TYPE * data;    /* 数据域 */
    int size;               /* 堆元素个数 */
    int capacity;           /* 容量 */

    /* 回调函数 */
    int (*compareFunc)(ELEMENT_TYPE arg1, ELEMENT_TYPE arg2);
} BinaryHeap;

/* 二叉堆的初始化 */
int binaryHeapInit(BinaryHeap * heap, int (*compareFunc)(ELEMENT_TYPE arg1, ELEMENT_TYPE arg2));

/* 二叉堆的新增 */
int binaryHeapInsert(BinaryHeap * heap, ELEMENT_TYPE data);

/* 二叉堆的删除 */
int binaryHeapDelete(BinaryHeap * heap);

/* 二叉堆 堆顶元素 */
int binaryHeapTop(BinaryHeap * heap, ELEMENT_TYPE *data);

/* 二叉堆元素个数 */
int binaryHeapGetSize(BinaryHeap * heap, int * pSize);

/* 二叉堆是否为空 */
bool binaryHeapIsEmpty(BinaryHeap * heap);

/* 二叉堆的销毁 */
int binaryHeapDetroy(BinaryHeap * heap);

#endif //_BINARY_HEAP_H__