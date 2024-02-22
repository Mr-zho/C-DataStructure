#include "doubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DoubleLinkNode
{
    /* 数据域 */
    ELEMENTTYPE data;
    /* 指针域 */
    struct DoubleLinkNode *prev;        /* prev指针 */
    struct DoubleLinkNode *next;        /* next指针 */
};

struct DoubleLinkList
{
    /* 链表的长度(结点个数) */
    int size;
    /* 链表的头结点 (虚拟头结点) */
    DoubleLinkNode * head;
    /* 链表的尾指针 */
    DoubleLinkNode * tail;
};

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    MALLOC_ERROR,
    NULL_PTR,
    INVALID_ACCESS,
};

/* 静态函数前置声明 */
static DoubleLinkNode *createDoubleLinkNode(ELEMENTTYPE data);
static int DoubleLinkListAccordAppointDataGetPos(DoubleLinkList *pList, ELEMENTTYPE data, int *pos, int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2));


/* 创建一个链表结点 */
static DoubleLinkNode *createDoubleLinkNode(ELEMENTTYPE data)
{
    DoubleLinkNode * newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if (newNode == NULL)
    {
        perror("malloc error");
        return NULL;
    }
    /* 清除脏数据 */
    memset(newNode, 0, sizeof(DoubleLinkNode) * 1);
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList **pList)
{   
    /* 初始化 */
    DoubleLinkList *list = NULL;
    do
    {
        list = (DoubleLinkList *)malloc(sizeof(DoubleLinkList) * 1);
        if (list == NULL)
        {
            perror("malloc error");
            break;
        }
        /* 清除脏数据 */
        memset(list, 0, sizeof(DoubleLinkList) * 1);

        list->head = createDoubleLinkNode(0);
        if (list->head == NULL)
        {
            perror("malloc error");
            break;
        }
        /* 初始化的时候, 将尾指针指向头 */
        list->tail = list->head;

        /* 初始化链表结点个数为0. */
        list->size = 0;

        /* 解引用 */
        *pList = list;


        return ON_SUCCESS;
    } while(0);

    /* 释放堆空间 */
    if (list != NULL && list->head != NULL)
    {
        free(list->head);
        list->head = NULL;
    }

    if (list != NULL)
    {
        free(list);
        list = NULL;
    }

    return MALLOC_ERROR; 
}


/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList *pList, ELEMENTTYPE data)
{
    return DoubleLinkListAppointPosInsert(pList, 0, data);
}

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList *pList, ELEMENTTYPE data)
{
    return DoubleLinkListAppointPosInsert(pList, pList->size, data);
}

/* 链表任意位置插 */
int DoubleLinkListAppointPosInsert(DoubleLinkList *pList, int pos, ELEMENTTYPE data)
{
    /* 判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    /* 判断位置合法性 todo... */
    if (pos < 0 || pos > pList->size)
    {
        return INVALID_ACCESS;
    }   

    /* 把数据封装成结点 */
    DoubleLinkNode * newNode = createDoubleLinkNode(data);
    if (newNode == NULL)
    {
        perror("malloc error");
        return MALLOC_ERROR;
    }
    
    /* head 是虚拟头结点 */
    DoubleLinkNode * travelNode = pList->head;

    int flag = 0;
    if (pos == pList->size)
    {
        travelNode = pList->tail;

        /* 需要修改尾指针的标记 */
        flag = 1;

        #if 0
        newNode->next = travelNode->next;       // 1
        newNode->prev = travelNode;             // 2
        // travelNode->next->prev = newNode;       // 3
        travelNode->next = newNode;             // 4
        #endif
    }
    else
    {
        while (pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
        #if 0
        /* 挂结点 */
        newNode->next = travelNode->next;       // 1
        newNode->prev = travelNode;             // 2
        travelNode->next->prev = newNode;       // 3
        travelNode->next = newNode;             // 4
        #endif 
    }
    /* 挂结点 */
    newNode->next = travelNode->next;       // 1
    newNode->prev = travelNode;             // 2
    if (flag == 0)
    {
        travelNode->next->prev = newNode;       // 3
    }
    travelNode->next = newNode;             // 4
   

    if (flag == 1)
    {
        /* 移动尾指针 */
        pList->tail = newNode;
    }

    /* 链表的元素个数加一 */
    (pList->size)++;

    return ON_SUCCESS;
}


/* 链表的遍历 */
int DoubleLinkListForeach(DoubleLinkList *pList, int (*printFunc)(ELEMENTTYPE))
{
    /* 判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    DoubleLinkNode * travelNode = pList->head->next;

    while (travelNode != NULL)
    {
#if 0
        printf("val: %d\n", *(int *)(travelNode->data));
#else
        printFunc(travelNode->data);
#endif

        /* 查找下一个结点 */
        travelNode = travelNode->next;
    }

    return ON_SUCCESS;
}

/* 获取链表的长度 */
int DoubleLinkListGetSize(DoubleLinkList *pList, int *pSize)
{
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pSize)
    {
        *pSize = pList->size;
    }
    
    return ON_SUCCESS;
}


/* 链表的头删 */
int DoubleLinkListHeadDelete(DoubleLinkList *pList)
{
    return DoubleLinkListAppointPosDelete(pList, 0);
}

/* 链表的尾删 */
int DoubleLinkListTailDelete(DoubleLinkList *pList)
{
    return DoubleLinkListAppointPosDelete(pList, pList->size - 1);
}

/* 链表删除任意位置 */
int DoubleLinkListAppointPosDelete(DoubleLinkList *pList, int pos)
{
    /* 判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    /* 判断位置合法性 */
    if (pos < 0 || pos > pList->size - 1)
    {   
        return INVALID_ACCESS;
    }

    DoubleLinkNode * travelNode  = pList->head;

    DoubleLinkNode * delNode = NULL;
    int flag = 0;
    if (pos == pList->size - 1)
    {
        /* 需要移动尾指针的标记 */
        flag = 1;

        /* 尾指针指向的结点 是要删除的结点 */
        delNode = pList->tail;
        /* 尾指针移动 */
        travelNode = delNode->prev;
        /* 手动置为NULL */
        travelNode->next = NULL;
    }
    else
    {
        while (pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
        /* 退出循环的条件: travelNode是我要删除结点的前一个结点 */
        delNode = travelNode->next;
        travelNode->next = delNode->next;
        delNode->next->prev = travelNode;
    }

    if (flag == 1)
    {
        pList->tail = travelNode;
    }

    /* 释放堆空间 */
    if (delNode != NULL)
    {
        free(delNode);
        delNode = NULL;
    }

    /* 链表的元素个数减一 */
    pList->size--;

    return ON_SUCCESS;
}

/* 根据值 获得链表的位置 */
static int DoubleLinkListAccordAppointDataGetPos(DoubleLinkList *pList, ELEMENTTYPE data, int *pos, int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2))
{   
    DoubleLinkNode * travelNode = pList->head->next;

    int position = 0;
    while (travelNode != NULL)
    {
        int cmp = compareFunc(data, travelNode->data);
        if (cmp == 0)
        {
            *pos = position;
            return position;
        }
        travelNode = travelNode->next;
        position++;
    }
    *pos = -1;

    return -1;
}

/* 链表删除任意的值 */
int DoubleLinkListAppointDataDelete(DoubleLinkList *pList, ELEMENTTYPE data, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    int pos = -1;
    while (DoubleLinkListAccordAppointDataGetPos(pList, data, &pos, compareFunc) != -1)
    {
        DoubleLinkListAppointPosDelete(pList, pos);
    }

    return ON_SUCCESS;
}

/* 链表的释放 */
int DoubleLinkListDestroy(DoubleLinkList *pList)
{
    /* 判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    while (pList->size != 0)
    {   
        DoubleLinkListHeadDelete(pList);
    }

    /* 释放虚拟头结点 */
    if (pList->head != NULL)
    {
        free(pList->head);
        pList->head = NULL;
    }

    if (pList != NULL)
    {
        free(pList);
        pList = NULL;
    }
    
    return ON_SUCCESS;
}


/* 链表的反向遍历 */
int DoubleLinkListReverseForeach(DoubleLinkList *pList, int (*printFunc)(ELEMENTTYPE))
{
    /* 判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    DoubleLinkNode * travelNode = pList->tail;
    while (travelNode != pList->head)
    {
        printFunc(travelNode->data);

        travelNode = travelNode->prev;
    }

    /* 退出条件是: 碰到虚拟头结点 */
    return ON_SUCCESS;
}

/* 获取链表的头的元素 */
int DoubleLinkListGetHeadPositionData(DoubleLinkList *pList, ELEMENTTYPE *data)
{
    return DoubleLinkListGetAppointPositionData(pList, 0, data);
}

/* 获取链表的尾部元素 */
int DoubleLinkListGetTailPositionData(DoubleLinkList *pList, ELEMENTTYPE *data)
{
    return DoubleLinkListGetAppointPositionData(pList, pList->size - 1, data);
}

/* 获取链表任意位置的元素 */
int DoubleLinkListGetAppointPositionData(DoubleLinkList *pList, int pos, ELEMENTTYPE *data)
{
    /* 判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    /* 判断位置的合法性 */
    if (pos < 0 || pos > pList->size - 1)
    {
        return INVALID_ACCESS;
    }

    DoubleLinkNode * travelNode = pList->head->next;

    /* 取最后一个元素 */
    if (pos == pList->size - 1)
    {
        travelNode = pList->tail;
    }
    else
    {
        while (pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
        /* 出了这个循环, travelNode到底是啥? */
        /* travelNode 就是我要找的结点 */
    }

    if (data)
    {
        *data = travelNode->data;
    }

    return ON_SUCCESS;
}