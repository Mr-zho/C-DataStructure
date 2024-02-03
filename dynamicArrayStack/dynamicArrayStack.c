#include "dynamicArrayStack.h"


/* 初始化栈 */
int dynamicArrayStackInit(DynamicArrayStack *pStack)
{
    return dynamicArrayInit(pStack, 10);
}

/* 压栈 */
int dynamicArrayStackPush(DynamicArrayStack *pStack, ELEMENTTYPE data)
{
    return dynamicArrayInsertData(pStack, data);
}

/* 出栈 */
int dynamicArrayStackPop(DynamicArrayStack *pStack)
{
    return dynamicArrayDeleteData(pStack);
}

/* 查看栈顶元素 */
int dynamicArrayStackTop(DynamicArrayStack *pStack, ELEMENTTYPE *data)
{
    int size = 0;
    dynamicArrayGetSize(pStack, &size);
    return dynamicArrayGetAppointPosData(pStack, size - 1, data);
}

/* 栈的元素个数 */
int dynamicArrayStackGetSize(DynamicArrayStack *pStack, int *pSize)
{
    dynamicArrayGetSize(pStack, pSize);
    int size = *pSize;
    return size;
}

/* 栈是否为空 */
int dynamicArrayStackIsEmpty(DynamicArrayStack *pStack)
{
    int size = 0;
    dynamicArrayGetSize(pStack, &size);

    return size == 0 ? 1 : 0;
}

/* 栈销毁 */
int dynamicArrayStackDestroy(DynamicArrayStack *pStack)
{
    return dynamicArrayDestroy(pStack);
}


