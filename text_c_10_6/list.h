#ifndef LIST_H
#define LIST_H

/* 双向链表节点：data 存数据，prev 指向前驱，next 指向后继 */
typedef struct Node
{
	int data;
	struct Node* prev;
	struct Node* next;
}Node;

Node* createList(void);                      /* 创建空链表，返回 NULL */
Node* createNode(int data);                  /* 创建并初始化一个新节点 */
void pushFront(Node** head, int data);       /* 头插：在链表最前面插入节点 */
void pushBack(Node** head, int data);        /* 尾插：在链表最后面插入节点 */
int insertAfter(Node* head, int pos, int data); /* 在第 pos 个节点后插入，成功返回 1 */
int deleteNode(Node** head, int data);       /* 按值删除第一个匹配节点，成功返回 1 */
void printForward(Node* head);               /* 正向遍历：head -> tail */
void printBackward(Node* head);              /* 反向遍历：tail -> head */
void freeList(Node** head);                  /* 释放全部节点，头指针置空 */

#endif
