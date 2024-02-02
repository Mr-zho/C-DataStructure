#include <stdio.h>
#include <string.h>
#include "linkList.h"


#define BUFFER_SIZE 5

int main()
{
    LinkList *list = NULL;
    LinkListInit(&list);
    

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
    LinkListForeach(list);
    return 0;
}

