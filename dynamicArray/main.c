#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>

#define BUFFER_SIZE 32
typedef struct StuInfo
{
    int age;
    char name[BUFFER_SIZE];
} StuInfo;


int compareFunc(void *arg1, void *arg2)
{
    int val1 = *(int *)arg1;
    int val2 = *(int *)arg2;

    return val1 - val2;
}

int main()
{
    DynamicArray array;
    memset(&array, 0, sizeof(array));

    
    dynamicArrayInit(&array, 5);
#if 0
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
#endif

    int data1 = 5;
    dynamicArrayInsertData(&array, (void *)&data1);
    int data2 = 10;
    dynamicArrayInsertData(&array, (void *)&data2);

    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);


    int *value = NULL;
    dynamicArrayGetAppointPosData(&array, 0, (void **)&value);
    printf("value:%d\n", *value);

    int delData = 10;
    dynamicArrayDeleteAppointData(&array, (void *)&delData, compareFunc);
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);


    /* 释放 */
    dynamicArrayDestroy(&array);

    return 0;
}