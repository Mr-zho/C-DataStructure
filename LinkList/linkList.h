#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#define ELEMENTTYPE void *

typedef struct LinkNode LinkNode;
typedef struct LinkList LinkList;

 
/* 链表初始化 */
int LinkListInit(LinkList **pList);


/* 链表头插 */
int LinkListHeadInsert(LinkList *pList, ELEMENTTYPE data);

/* 链表尾插 */
int LinkListTailInsert(LinkList *pList, ELEMENTTYPE data);

/* 链表任意位置插 */
int LinkListAppointPosInsert(LinkList *pList, int pos, ELEMENTTYPE data);

/* 链表的遍历 */
int LinkListForeach(LinkList *pList, int (*printFunc)(ELEMENTTYPE));

/* 获取链表的长度 */
int LinkListGetSize(LinkList *pList, int *pSize);

/* 链表的头删 */
int LinkListHeadDelete(LinkList *pList);

/* 链表的尾删 */
int LinkListTailDelete(LinkList *pList);

/* 链表删除任意位置 */
int LinkListAppointPosDelete(LinkList *pList, int pos);

/* 链表删除任意的值 */
int LinkListAppointDataDelete(LinkList *pList, ELEMENTTYPE data, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));

/* 链表的释放 */
int LinkListDestroy(LinkList *pList);
#endif