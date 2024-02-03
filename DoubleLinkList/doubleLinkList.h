#ifndef __DoubleLinkList_H__
#define __DoubleLinkList_H__

#define ELEMENTTYPE void *

typedef struct DoubleLinkNode DoubleLinkNode;
typedef struct DoubleLinkList DoubleLinkList;

 
/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList **pList);

/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList *pList, ELEMENTTYPE data);

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList *pList, ELEMENTTYPE data);

/* 链表任意位置插 */
int DoubleLinkListAppointPosInsert(DoubleLinkList *pList, int pos, ELEMENTTYPE data);

/* 链表的遍历 */
int DoubleLinkListForeach(DoubleLinkList *pList, int (*printFunc)(ELEMENTTYPE));

/* 获取链表的长度 */
int DoubleLinkListGetSize(DoubleLinkList *pList, int *pSize);

/* 链表的头删 */
int DoubleLinkListHeadDelete(DoubleLinkList *pList);

/* 链表的尾删 */
int DoubleLinkListTailDelete(DoubleLinkList *pList);

/* 链表删除任意位置 */
int DoubleLinkListAppointPosDelete(DoubleLinkList *pList, int pos);

/* 链表删除任意的值 */
int DoubleLinkListAppointDataDelete(DoubleLinkList *pList, ELEMENTTYPE data, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));

/* 链表的释放 */
int DoubleLinkListDestroy(DoubleLinkList *pList);
#endif