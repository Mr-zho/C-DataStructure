#include "dynamicArray.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    MALLOC_ERROR,
    NULL_PTR,
    INVALID_ACCESS,
};

#define DEFAULR_CAPACITY    10


/* 静态函数前置声明 */
static int expandDynamicArrayCapacity(DynamicArray *pArray);
static int shrinkDynamicArrayCapacity(DynamicArray *pArray);
/* 根据元素的值 获得对应的位置 */
static int dynamicArrayAppointDataGetPos(DynamicArray *pArray, ELEMENTTYPE data, int *pos, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));



/* 动态数组初始化 */
int dynamicArrayInit(DynamicArray *pArray, int capacity)
{
    int ret = 0;
    if (pArray == NULL)
    {
        printf("null ptr error\n");
        return NULL_PTR;
    }

    if (capacity <= 0)
    {
        capacity = DEFAULR_CAPACITY;
    }

    /* 分配堆空间 */ 
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * capacity);
    if (pArray->data == NULL)
    {
        printf("malloc error\n");
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * capacity);

    /* 初始化的时候, 元素个数为0 */
    pArray->size = 0;
    pArray->capacity = capacity;

    return ON_SUCCESS;
}

/* 静态函数: 只在本源文件中使用 */
static int expandDynamicArrayCapacity(DynamicArray *pArray)
{
    int ret = 0;
    /* 1. 数据备份 */
    ELEMENTTYPE * tmpData = pArray->data;

    /* 2. 需要扩大的容量 */
    int needExpandCapacity = pArray->capacity + (pArray->capacity >> 1);
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needExpandCapacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * needExpandCapacity);

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

/* 动态数组插入元素 (默认插到数组末尾位置) */
int dynamicArrayInsertData(DynamicArray *pArray, ELEMENTTYPE data)
{
    return dynamicArrayAppointPosInsertData(pArray, pArray->size, data);
}


/* 动态数组在指定位置插入元素 */
int dynamicArrayAppointPosInsertData(DynamicArray *pArray, int pos, ELEMENTTYPE data)
{
    int ret = 0;
    /* 判空 */
    if (pArray == NULL)
    {
        printf("null ptr error\n");
        return NULL_PTR;
    }

    /* 判断位置是否合法 */
    if (pos < 0 || pos > pArray->size)
    {
        return INVALID_ACCESS;
    }

    /* 空间不足预警算法是: 元素个数的1.5倍 > 数组容量 */
    if (pArray->size + (pArray->size >> 1) > pArray->capacity)
    {
        /* 扩容 */
        expandDynamicArrayCapacity(pArray);
    }

    /* 从后往前移动 */
    for (int idx = pArray->size; idx > pos; idx--)
    {
        pArray->data[idx] = pArray->data[idx - 1];
    }
    /* 赋值 */
    pArray->data[pos] = data;

    /* 更新数组属性 */
    (pArray->size)++;

    return ret;
}

/* API: application programming interface */
/* 获取数组的元素个数 */
int dynamicArrayGetSize(DynamicArray *pArray, int *pSize)
{
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    if (pSize != NULL)
    {
        /* 解引用 */
        *pSize = pArray->size;
    }

    return ON_SUCCESS;
}

/* 获取数组的容量大小 */
int dynamicArrayGetCapacity(DynamicArray *pArray, int *pCapacity)
{   
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    if (pCapacity != NULL)
    {
        /* 解引用 */
        *pCapacity = pArray->capacity;
    }

    return ON_SUCCESS;
}

/* 动态数组删除元素 (默认删除数组末尾位置) */
int dynamicArrayDeleteData(DynamicArray *pArray)
{
    return dynamicArrayAppointPosDeleteData(pArray, pArray->size - 1);
}

static int shrinkDynamicArrayCapacity(DynamicArray *pArray)
{
    /* 1. 数据备份 */
    ELEMENTTYPE * tmpData = pArray->data;

    /* 2. 开辟一块更小的空间 */
    int needShrinkCapacity = pArray->capacity - (pArray->capacity >> 1);
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needShrinkCapacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * needShrinkCapacity);

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

    /* 5. 更新数组属性 */
    pArray->capacity = needShrinkCapacity;

    return ON_SUCCESS;
}

/* 动态数组在指定位置删除元素 */
int dynamicArrayAppointPosDeleteData(DynamicArray *pArray, int pos)
{
    /* 判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    
    /* 判断位置合法性 */
    if (pos < 0 || pos >= pArray->size)
    {
        return INVALID_ACCESS;
    }

    /* 缩容 */
    if (pArray->size < pArray->capacity - (pArray->capacity >> 1))
    {
        shrinkDynamicArrayCapacity(pArray);
    }

    for (int idx = pos; idx < pArray->size - 1; idx++)
    {
        pArray->data[idx] = pArray->data[idx + 1];
    }

    /* 更新数组的属性 */
    (pArray->size)--;

    return ON_SUCCESS;
}

/* 根据元素的值 获得对应的位置 */
static int dynamicArrayAppointDataGetPos(DynamicArray *pArray, ELEMENTTYPE data, int *pos, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    for (int idx = 0; idx < pArray->size; idx++)
    {
        #if 0
        if (data == pArray->data[idx])
        {
            *pos = idx;
            return ON_SUCCESS;
        }
        #elif 0
        if (*(int *)data == *(int*)(pArray->data[idx]))
        {
            *pos = idx;
            return ON_SUCCESS;
        }
        #else
        /* 比较器 -> 回调函数 -> 钩子函数 */
        int cmp = compareFunc(data, pArray->data[idx]);
        if (cmp == 0)
        {
            *pos = idx;
            return ON_SUCCESS;
        }
        #endif
    }
    *pos = -1;

    return -1;
}

/* 动态数组删除指定的值 */
int dynamicArrayDeleteAppointData(DynamicArray *pArray, ELEMENTTYPE data, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    /* 判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    int pos = -1;
    while (dynamicArrayAppointDataGetPos(pArray, data, &pos, compareFunc) != -1)
    {
        dynamicArrayAppointPosDeleteData(pArray, pos);
    }
    
    return 0;
}

/* 获取指定位置的值 */
int dynamicArrayGetAppointPosData(DynamicArray *pArray, int pos, ELEMENTTYPE *data)
{
    /* 判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    /* 判断位置的合法性 */
    if (pos < 0 || pos >= pArray->size)
    {
        return INVALID_ACCESS;
    }  

    if (data != NULL)
    {
        *data = pArray->data[pos];
    }

    return ON_SUCCESS;
}

/* 销毁动态数组 */
int dynamicArrayDestroy(DynamicArray *pArray)
{
    if (pArray == NULL)
    {
        return NULL_PTR;
    }

    if (pArray->data != NULL)
    {
        free(pArray->data);
        pArray->data = NULL;
    }

    return ON_SUCCESS;
}