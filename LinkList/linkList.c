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

    while (pos)
    {
        travelNode = travelNode->next;
        pos--;
    }

    /* 挂结点 */
    newNode->next = travelNode->next;       // 1
    travelNode->next = newNode;             // 2

    /* 链表的元素个数加一 */
    (pList->size)++;

    return ON_SUCCESS;
}