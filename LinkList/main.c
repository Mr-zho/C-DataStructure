#include <stdio.h>
#include <string.h>
#include "linkList.h"


#define BUFFER_SIZE 5

int printData(void *arg)
{
    int val = *(int *)arg;
    printf("val:%d\n", val);
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

int main()
{
    LinkList *list = NULL;
    LinkListInit(&list);
    

#if 0
    int nums[BUFFER_SIZE] = {11, 22, 33, 44, 55};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        LinkListHeadInsert(list, (void *)&nums[idx]);
    }

    int posVal = 666;
    LinkListAppointPosInsert(list, 3, &posVal);

    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        LinkListTailInsert(list, (void *)&nums[idx]);
    }
    int size = 0;
    LinkListGetSize(list, &size);
    printf("size:%d\n", size);

    /* 遍历 */
    LinkListForeach(list, printData);
#endif

#if 1
    /* 符合数据类型 */
    StuInfo stu1, stu2, stu3;
    stu1.age = 22;
    strcpy(stu1.name, "liwenbo");

    stu2.age = 26;
    strcpy(stu2.name, "mr_zhou");

    stu3.age = 19;
    strcpy(stu3.name, "xiaoyu");

    LinkListHeadInsert(list, (void *)&stu1);
    LinkListHeadInsert(list, (void *)&stu2);
    LinkListHeadInsert(list, (void *)&stu3);

    int size = 0;
    LinkListGetSize(list, &size);
    printf("size:%d\n", size);

    LinkListForeach(list, printStruct);
    
#endif
    return 0;
}

