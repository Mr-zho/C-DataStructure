#include <stdio.h>
#include "binaryHeap.h"
#include <stdlib.h>
#include <string.h>

#define DEFALUT_CAPACITY    10

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    MALLOC_ERROR,
    NULL_PTR,
    INVALID_ACCESS,
};

/* 静态函数初始化 */
/* 上浮 */
static int floatUp(BinaryHeap * heap, int index);
/* 下沉 */
static int sinkDown(BinaryHeap * heap, int index);
/* 扩容 */
static int expandBinaryHeapCapacity(BinaryHeap *pArray);
/* 缩容 */
static int shrinkBinaryHeapCapacity(BinaryHeap *pArray);

/* 二叉堆的初始化 */
int binaryHeapInit(BinaryHeap * heap, int (*compareFunc)(ELEMENT_TYPE arg1, ELEMENT_TYPE arg2))
{
    if (heap == NULL)
    {
        return NULL_PTR;
    }
    
    heap->capacity = DEFALUT_CAPACITY;
    heap->data = (ELEMENT_TYPE *)malloc(sizeof(ELEMENT_TYPE) * heap->capacity);
    if (heap->data == NULL)
    {
        perror("malloc error");
        exit(-1);
    }
    /* 清空脏数据 */
    memset(heap->data, 0, sizeof(ELEMENT_TYPE) * heap->capacity);
    /* 初始化元素个数 */
    heap->size = 0;


    /* 比较器 */
    heap->compareFunc = compareFunc;

    return ON_SUCCESS;
}


/* 静态函数: 只在本源文件中使用 */
static int expandBinaryHeapCapacity(BinaryHeap *pArray)
{
    int ret = 0;
    /* 1. 数据备份 */
    ELEMENT_TYPE * tmpData = pArray->data;

    /* 2. 需要扩大的容量 */
    int needExpandCapacity = pArray->capacity + (pArray->capacity >> 1);
    pArray->data = (ELEMENT_TYPE *)malloc(sizeof(ELEMENT_TYPE) * needExpandCapacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENT_TYPE) * needExpandCapacity);

    /* 3. 数据迁移 */
    for (int idx = 0; idx < pArray->size; idx++)
    {
        pArray->data[idx] = tmpData[idx];
    }

    /* 4. 释放内存 */
    if (tmpData != NULL)
    {
        free(tmpData);
        tmpData = NULL;
    }

    /* 5. 更新数组的属性 */
    pArray->capacity = needExpandCapacity;

    return ret;
}

/* 小顶堆 */
static int floatUp(BinaryHeap * heap, int index)
{
    /* 当前结点的值 */
    ELEMENT_TYPE curIndexVal = heap->data[index];

#if 0
    int cmp = 0;
    while (index > 0)
    {
        /* 父结点索引 */
        int parentIndex = (index - 1) >> 1;

        cmp = heap->compareFunc(heap->data[index], heap->data[parentIndex]);
        if (cmp > 0)
        {
            break;
        }

        /* 交换元素的值 */
        ELEMENT_TYPE tmpData = heap->data[index];
        heap->data[index] = heap->data[parentIndex];
        heap->data[parentIndex] = tmpData;

        index = parentIndex;
    }
#else

    int cmp = 0;
    while (index > 0)
    {
        /* 父结点索引 */
        int parentIndex = (index - 1) >> 1;

        cmp = heap->compareFunc(curIndexVal, heap->data[parentIndex]);
        if (cmp > 0)
        {
            break;
        }

        /* 将父结点元素值 拷贝到 当前位置 */
        heap->data[index] = heap->data[parentIndex];

        index = parentIndex;
    }
    /* 最后赋值 */
    heap->data[index] = curIndexVal;

#endif

    return ON_SUCCESS;
}


/* 二叉堆的新增 */
int binaryHeapInsert(BinaryHeap * heap, ELEMENT_TYPE data)
{
    if (heap == NULL)
    {
        return NULL_PTR;
    }

    /* 判断容量是否满 */
    if (heap->size == heap->capacity)
    {
        expandBinaryHeapCapacity(heap);
    }

    heap->data[(heap->size)] = data;

    /* 是否满足堆的特性 */
    /* 上浮 */
    floatUp(heap, heap->size);

    /* 更新元素个数 */
    (heap->size)++;

    return ON_SUCCESS;
}

/* 下沉 */
static int sinkDown(BinaryHeap * heap, int index)
{
    ELEMENT_TYPE currentData = heap->data[index];

    int cmp = 0;
    /* 第一个叶子结点的索引 = 非叶子结点的数量 */
    /* 必须保证index位置是非叶子结点  */
    int halfIndex = heap->size >> 1;
    while (index < halfIndex)
    {
        /* index的结点 有两种情况 */
        /* 1. 有两个子结点 */
        /* 2. 有一个子结点: 一定是左结点 */
        
        /* 默认为左子结点 */
        int childIndex = (index << 1) + 1;

        /* 右子结点 */
        int rightIndex = childIndex + 1;

        /* 选出左右子结点中 较小的值 */
        if (rightIndex < heap->size && heap->compareFunc(heap->data[rightIndex], heap->data[childIndex]) < 0)
        {
            childIndex = rightIndex;
        }

        /* 比较 */
        cmp = heap->compareFunc(currentData, heap->data[childIndex]);
        if (cmp < 0)
        {
            break;
        }

        /* 将子结点的值存放到当前位置 */
        heap->data[index] = heap->data[childIndex];

        /* 更新结点index */
        index = childIndex;
    }
    heap->data[index] = currentData;

    return ON_SUCCESS;
}

/* 二叉堆的删除 */
int binaryHeapDelete(BinaryHeap * heap)
{
    if (heap == NULL)
    {
        return NULL_PTR;
    }

    /* 没有元素 */
    if (heap->size == 0)
    {
        return INVALID_ACCESS;
    }

    /* 至少有一个元素 */
    /* 覆盖 */
    heap->data[0] = heap->data[--(heap->size)];
    
    /* 下沉 */
    sinkDown(heap, 0);

    return ON_SUCCESS;
}

/* 二叉堆 堆顶元素 */
int binaryHeapTop(BinaryHeap * heap, ELEMENT_TYPE *data)
{
    if (heap == NULL)
    {
        return NULL_PTR;
    }

    if (data)
    {
        *data = heap->data[0];
    }

    return ON_SUCCESS;
}

/* 二叉堆元素个数 */
int binaryHeapGetSize(BinaryHeap * heap, int * pSize)
{
    if (heap == NULL || pSize == NULL)
    {
        return NULL_PTR;
    }

    *pSize = heap->size;

    return ON_SUCCESS;
}

/* 二叉堆是否为空 */
bool binaryHeapIsEmpty(BinaryHeap * heap)
{
    return heap->size == 0;
}

/* 二叉堆的销毁 */
int binaryHeapDetroy(BinaryHeap * heap)
{
    if (heap == NULL)
    {
        return NULL_PTR;
    }

    if (heap->data != NULL)
    {
        free(heap->data);
        heap->data = NULL;
    }

    return ON_SUCCESS;
}

