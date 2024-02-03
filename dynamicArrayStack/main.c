#include "dynamicArrayStack.h"
#include <stdio.h>

#define BUFFER_SIZE 5

int main()
{
    DynamicArrayStack stack;
    dynamicArrayStackInit(&stack);

    int nums[BUFFER_SIZE] = {11, 22, 33, 44, 55};

    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        dynamicArrayStackPush(&stack, (void *)&nums[idx]);
    }
    
    int size = 0;
    dynamicArrayStackGetSize(&stack, &size);
    printf("size:%d\n", size);

    int *topVal = NULL;
    while (dynamicArrayStackGetSize(&stack, &size) != 0)
    {
        dynamicArrayStackTop(&stack, (void **)&topVal);
        dynamicArrayStackPop(&stack);

        printf("top value:%d\n", *topVal);
    }

    /* 销毁 */
    dynamicArrayStackDestroy(&stack);
}