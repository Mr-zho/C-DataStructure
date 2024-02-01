#include "linkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinKNode
{
    /* 数据域 */
    ELEMENTTYPE data;
    /* 指针域 */
    struct LinKNode *next;
};

struct LinkList
{
    /* 链表的长度(结点个数) */
    int size;
    /* 链表的头结点 (虚拟头结点) */
    LinKNode * head;
};

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    MALLOC_ERROR,
    NULL_PTR,
    INVALID_ACCESS,
};

/* 链表初始化 */
int LinkListInit(LinkList **pList)
{
    do
    {
        LinkList *list = (LinkList *)malloc(sizeof(LinkList) * 1);
        if (list == NULL)
        {
            perror("malloc error");
            break;
        }
        /* 清除脏数据 */
        memset(list, 0, sizeof(LinkList) * 1);

        list->head = (LinKNode *)malloc(sizeof(LinKNode) * 1);
        if (list->head == NULL)
        {
            perror("malloc error");
            break;
        }
        /* 清除脏数据 */
        memset(list->head, 0, sizeof(LinKNode) * 1);
        /* 虚拟头结点 不存放数据 */
        list->head->data = 0;
        list->head->next = NULL;


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