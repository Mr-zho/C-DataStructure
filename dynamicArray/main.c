#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>

int main()
{
    DynamicArray array;
    memset(&array, 0, sizeof(array));

    dynamicArrayInit(&array, 5);

    int size = 0;
    dynamicArrayGetSize(&array, &size);
    int capacity = 0;
    dynamicArrayGetCapacity(&array, &capacity);
    printf("size:%d,\tcapacity:%d\n", size, capacity);


    for (int idx = 0; idx < 4; idx++)
    {
        dynamicArrayInsertData(&array, idx + 1);
        dynamicArrayInsertData(&array, idx + 1);

    }

    dynamicArrayGetSize(&array, &size);
    dynamicArrayGetCapacity(&array, &capacity);
    printf("size:%d,\tcapacity:%d\n", size, capacity);


    int value = 0;
    for (int idx = 0; idx < size; idx++)
    {
        dynamicArrayGetAppointPosData(&array, idx, &value);
        printf("value:%d\t", value);
    }   
    printf("\n");

    dynamicArrayAppointPosInsertData(&array, 2, 666);
    dynamicArrayGetSize(&array, &size);
    for (int idx = 0; idx < size; idx++)
    {
        dynamicArrayGetAppointPosData(&array, idx, &value);
        printf("value:%d\t", value);
    }   
    printf("\n");

    dynamicArrayAppointPosDeleteData(&array, 4);
    dynamicArrayGetSize(&array, &size);
    for (int idx = 0; idx < size; idx++)
    {
        dynamicArrayGetAppointPosData(&array, idx, &value);
        printf("value:%d\t", value);
    }   
    printf("\n");


    dynamicArrayDeleteAppointData(&array, 3);
    dynamicArrayGetSize(&array, &size);
    for (int idx = 0; idx < size; idx++)
    {
        dynamicArrayGetAppointPosData(&array, idx, &value);
        printf("value:%d\t", value);
    }   
    printf("\n");

    /* 释放 */
    dynamicArrayDestroy(&array);
    return 0;
}