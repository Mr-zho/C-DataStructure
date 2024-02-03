#include <stdio.h>
#include <string.h>
#include "doubleLinkList.h"


#define BUFFER_SIZE 4

int printData(void *arg)
{
    int val = *(int *)arg;
    printf("val:%d\t", val);
}

typedef struct StuInfo
{
    int age;
    char name[BUFFER_SIZE];
} StuInfo;


int printStruct(void *arg)
{
    int ret = 0;
    StuInfo * stu = (StuInfo *)arg;
    printf("age:%d,\t name:%s\n", stu->age, stu->name);

    return ret;
}


int compareFunc(void *arg1, void *arg2)
{
    int val1 = *(int *)arg1;
    int val2 = *(int *)arg2;

    return val1 - val2;
}

int main()
{
    DoubleLinkList *list = NULL;
    DoubleLinkListInit(&list);
    
    int nums[BUFFER_SIZE] = {11, 22, 33, 44};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        DoubleLinkListTailInsert(list, &nums[idx]);
    }    

    int size = 0;
    DoubleLinkListGetSize(list, &size);
    printf("size:%d\n", size);

    
    /* 逆序打印 */
    DoubleLinkListReverseForeach(list, printData);
    printf("\n");
    return 0;
}

