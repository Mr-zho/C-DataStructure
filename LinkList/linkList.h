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
int LinkListAppointPosInsert(LinkList *pList, int pos, ELEMENTTYPE data);\

/* 链表的遍历 */
int LinkListForeach(LinkList *pList);

#endif