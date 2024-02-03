#ifndef __DYNAMICARRAY_STACK_H__
#define __DYNAMICARRAY_STACK_H__

#include "common.h"

typedef DynamicArray DynamicArrayStack;

/* 初始化栈 */
int dynamicArrayStackInit(DynamicArrayStack *pStack);

/* 压栈 */
int dynamicArrayStackPush(DynamicArrayStack *pStack, ELEMENTTYPE data);

/* 出栈 */
int dynamicArrayStackPop(DynamicArrayStack *pStack);

/* 查看栈顶元素 */
int dynamicArrayStackTop(DynamicArrayStack *pStack, ELEMENTTYPE *data);

/* 栈的元素个数 */
int dynamicArrayStackGetSize(DynamicArrayStack *pStack, int *pSize);

/* 栈是否为空 */
int dynamicArrayStackIsEmpty(DynamicArrayStack *pStack);

/* 栈销毁 */
int dynamicArrayStackDestroy(DynamicArrayStack *pStack);


#endif // __DYNAMICARRAY_STACK_H__