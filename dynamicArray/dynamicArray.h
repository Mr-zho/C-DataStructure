#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#define ELEMENTTYPE  void *
/* 动态数组结构体 */
typedef struct DynamicArray DynamicArray;

/* 动态数组初始化 */
int dynamicArrayInit(DynamicArray *pArray, int capacity);

/* 动态数组插入元素 (默认插到数组末尾位置) */
int dynamicArrayInsertData(DynamicArray *pArray, ELEMENTTYPE data);

/* 动态数组在指定位置插入元素 */
int dynamicArrayAppointPosInsertData(DynamicArray *pArray, int pos, ELEMENTTYPE data);

/* 获取数组的元素个数 */
int dynamicArrayGetSize(DynamicArray *pArray, int *pSize);

/* 获取数组的容量大小 */
int dynamicArrayGetCapacity(DynamicArray *pArray, int *pCapacity);

/* 动态数组删除元素 (默认删除数组末尾位置) */
int dynamicArrayDeleteData(DynamicArray *pArray);

/* 动态数组在指定位置删除元素 */
int dynamicArrayAppointPosDeleteData(DynamicArray *pArray, int pos);

/* 动态数组删除指定的值 */
int dynamicArrayDeleteAppointData(DynamicArray *pArray, ELEMENTTYPE data, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));

/* 获取指定位置的值 */
int dynamicArrayGetAppointPosData(DynamicArray *pArray, int pos, ELEMENTTYPE *data);

/* 销毁动态数组 */
int dynamicArrayDestroy(DynamicArray *pArray);

#endif //__DYNAMIC_ARRAY_H__