#ifndef __COMMON_H_
#define __COMMON_H_

#define ELEMENTTYPE  void *
/* 动态数组结构体 */
typedef struct DynamicArray
{
    /* 数据 */
    ELEMENTTYPE * data;
    /* 元素个数 */
    int size;
    /* 容量大小 */
    int capacity;
} DynamicArray;

#endif //__COMMON_H_