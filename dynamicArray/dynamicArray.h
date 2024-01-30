#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#define ELEMENTTYPE int 
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

/* 动态数组初始化 */
int dynamicArrayInit(DynamicArray *pArray, int capacity);

/* 动态数组插入元素 (默认插到数组末尾位置) */
int dynamicArrayInsertData(DynamicArray *pArray, ELEMENTTYPE data);

/* 动态数组在指定位置插入元素 */
int dynamicArrayAppointPosInsertData(DynamicArray *pArray, int pos, ELEMENTTYPE data);





#endif //__DYNAMIC_ARRAY_H__