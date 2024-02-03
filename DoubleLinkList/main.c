#include <stdio.h>
#include <string.h>
#include "doubleLinkList.h"


#define BUFFER_SIZE 2

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
    
    int nums[BUFFER_SIZE] = {11, 22};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        DoubleLinkListTailInsert(list, &nums[idx]);
    }    

    int size = 0;
    DoubleLinkListGetSize(list, &size);
    printf("size:%d\n", size);

    
    /* 逆序打印 */
    printf("=======reverse print=========\n");
    DoubleLinkListReverseForeach(list, printData);
    printf("\n");
    
    /* 头插 */
    DoubleLinkListHeadInsert(list, &nums[0]);

    printf("=======sequence print=========\n");
    DoubleLinkListForeach(list, printData);
    printf("\n");

    /* 任意位置插 */
    int posValue = 666;
    DoubleLinkListAppointPosInsert(list, 2, &posValue);
    printf("=======sequence print=========\n");
    DoubleLinkListForeach(list, printData);
    printf("\n");


    printf("==============================================\n");
    /* 头删 */
    DoubleLinkListHeadDelete(list);
    printf("=======sequence print=========\n");
    DoubleLinkListForeach(list, printData);
    printf("\n");

    /* 任意位置删 */
    DoubleLinkListAppointPosDelete(list, 1);
    printf("=======sequence print=========\n");
    DoubleLinkListForeach(list, printData);
    printf("\n");

    /* 尾删 */
    DoubleLinkListTailDelete(list);
    printf("=======sequence print=========\n");
    DoubleLinkListForeach(list, printData);
    printf("\n");

    // printf("=======reverse print=========\n");
    // DoubleLinkListReverseForeach(list, printData);
    // printf("\n");
    #if 1
    DoubleLinkListTailDelete(list);
    printf("=======sequence print=========\n");
    DoubleLinkListForeach(list, printData);
    printf("\n");
    #else
    DoubleLinkListHeadDelete(list);
    printf("=======sequence print=========\n");
    DoubleLinkListForeach(list, printData);
    printf("\n");
    #endif

    DoubleLinkListGetSize(list, &size);
    printf("size:%d\n", size);


    DoubleLinkListTailInsert(list, &nums[0]);
    DoubleLinkListTailInsert(list, &nums[1]);

    DoubleLinkListGetSize(list, &size);
    printf("size:%d\n", size);
    printf("=======sequence print=========\n");
    DoubleLinkListForeach(list, printData);
    printf("\n");

    /* 链表释放 */
    DoubleLinkListDestroy(list);
    
    return 0;
}

