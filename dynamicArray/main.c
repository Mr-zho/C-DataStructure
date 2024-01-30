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


    for (int idx = 0; idx < 8; idx++)
    {
        dynamicArrayInsertData(&array, idx + 1);
    }

    dynamicArrayGetSize(&array, &size);
    dynamicArrayGetCapacity(&array, &capacity);
    printf("size:%d,\tcapacity:%d\n", size, capacity);

    return 0;
}