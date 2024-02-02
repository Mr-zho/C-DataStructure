#include "linkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkNode
{
    /* 数据域 */
    ELEMENTTYPE data;
    /* 指针域 */
    struct LinkNode *next;
};

struct LinkList
{
    /* 链表的长度(结点个数) */
    int size;
    /* 链表的头结点 (虚拟头结点) */
    LinkNode * head;
    /* 链表的尾指针 */
    LinkNode * tail;
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
static LinkNode *createLinkNode(ELEMENTTYPE data);
static int LinkListAccordAppointDataGetPos(LinkList *pList, ELEMENTTYPE data, int *pos, int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2));


/* 创建一个链表结点 */
static LinkNode *createLinkNode(ELEMENTTYPE data)
{
    LinkNode * newNode = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    if (newNode == NULL)
    {
        perror("malloc error");
        return NULL;
    }
    /* 清除脏数据 */
    memset(newNode, 0, sizeof(LinkNode) * 1);
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

/* 链表初始化 */
int LinkListInit(LinkList **pList)
{   
    /* 初始化 */
    LinkList *list = NULL;
    do
    {
        list = (LinkList *)malloc(sizeof(LinkList) * 1);
        if (list == NULL)
        {
            perror("malloc error");
            break;
        }
        /* 清除脏数据 */
        memset(list, 0, sizeof(LinkList) * 1);

        list->head = createLinkNode(0);
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
int LinkListHeadInsert(LinkList *pList, ELEMENTTYPE data)
{
    return LinkListAppointPosInsert(pList, 0, data);
}

/* 链表尾插 */
int LinkListTailInsert(LinkList *pList, ELEMENTTYPE data)
{
    return LinkListAppointPosInsert(pList, pList->size, data);
}

/* 链表任意位置插 */
int LinkListAppointPosInsert(LinkList *pList, int pos, ELEMENTTYPE data)
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
    LinkNode * newNode = createLinkNode(data);
    if (newNode == NULL)
    {
        perror("malloc error");
        return MALLOC_ERROR;
    }
    
    /* head 是虚拟头结点 */
    LinkNode * travelNode = pList->head;

    int flag = 0;
    if (pos == pList->size)
    {
        travelNode = pList->tail;

        /* 需要修改尾指针的标记 */
        flag = 1;
    }
    else
    {
        while (pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
    }
    /* 挂结点 */
    newNode->next = travelNode->next;       // 1
    travelNode->next = newNode;             // 2

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
int LinkListForeach(LinkList *pList, int (*printFunc)(ELEMENTTYPE))
{
    /* 判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    LinkNode * travelNode = pList->head->next;

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
int LinkListGetSize(LinkList *pList, int *pSize)
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
int LinkListHeadDelete(LinkList *pList)
{
    return LinkListAppointPosDelete(pList, 0);
}

/* 链表的尾删 */
int LinkListTailDelete(LinkList *pList)
{
    return LinkListAppointPosDelete(pList, pList->size - 1);
}

/* 链表删除任意位置 */
int LinkListAppointPosDelete(LinkList *pList, int pos)
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

    LinkNode * travelNode  = pList->head;

    int flag = 0;
    if (pos == pList->size - 1)
    {
        /* 需要移动尾指针的标记 */
        flag = 1;
    }

    while (pos)
    {
        travelNode = travelNode->next;
        pos--;
    }
    /* 退出循环的条件: travelNode是我要删除结点的前一个结点 */
    LinkNode * delNode = travelNode->next;
    travelNode->next = delNode->next;


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
static int LinkListAccordAppointDataGetPos(LinkList *pList, ELEMENTTYPE data, int *pos, int (*compareFunc)(ELEMENTTYPE arg1, ELEMENTTYPE arg2))
{   
    LinkNode * travelNode = pList->head->next;

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
int LinkListAppointDataDelete(LinkList *pList, ELEMENTTYPE data, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    int pos = -1;
    while (LinkListAccordAppointDataGetPos(pList, data, &pos, compareFunc) != -1)
    {
        LinkListAppointPosDelete(pList, pos);
    }

    return ON_SUCCESS;
}

/* 链表的释放 */
int LinkListDestroy(LinkList *pList)
{
    /* 判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    while (pList->size != 0)
    {   
        LinkListHeadDelete(pList);
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