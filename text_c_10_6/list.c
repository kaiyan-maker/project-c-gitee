#include<stdio.h>
#include<stdlib.h>
#include"list.h"

/*
 * 创建空链表
 * 空链表用 NULL 表示，所以直接返回 NULL
 */
Node* createList(void)
{
	return NULL;
}

/*
 * 创建一个新节点
 * 数据域赋值，前后指针都置为 NULL，由后续插入操作接上
 */
Node* createNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("内存分配失败\n");
		exit(1);
	}
	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

/*
 * 头插法
 * 新节点的 next 指向原头节点，原头节点的 prev 指回新节点，
 * 最后让 head 指向新节点（注意原链表为空时不能解引用 *head）
 */
void pushFront(Node** head, int data)
{
	Node* newNode = createNode(data);
	newNode->next = *head;
	if (*head != NULL)
		(*head)->prev = newNode;
	*head = newNode;
}

/*
 * 尾插法
 * 先走到尾节点（next == NULL），把尾节点的 next 指向新节点，
 * 新节点的 prev 指向尾节点（空链表则直接成为头节点）
 */
void pushBack(Node** head, int data)
{
	Node* newNode = createNode(data);
	if (*head == NULL)
	{
		*head = newNode;
		return;
	}
	Node* cur = *head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = newNode;
	newNode->prev = cur;
}

/*
 * 在第 pos 个节点（从 0 开始计数）之后插入新节点
 * 关键是改四个指针：新节点接前后，前后节点再接回新节点
 * pos 越界返回 0
 */
int insertAfter(Node* head, int pos, int data)
{
	Node* cur = head;
	for (int i = 0; i < pos && cur != NULL; i++)
		cur = cur->next;
	if (cur == NULL)
		return 0;

	Node* newNode = createNode(data);
	newNode->prev = cur;          /* 新节点前驱 = cur */
	newNode->next = cur->next;    /* 新节点后继 = cur 的原后继 */
	if (cur->next != NULL)
		cur->next->prev = newNode; /* 原后继的前驱改指新节点 */
	cur->next = newNode;          /* cur 的后继改指新节点 */
	return 1;
}

/*
 * 按值删除第一个 data 匹配的节点
 * 要点：
 *   1. 找到目标节点 cur
 *   2. 把前后节点"跨过" cur 直接连起来（注意 cur 是头节点时要更新 head）
 *   3. free 释放内存，否则泄漏
 * 未找到返回 0
 */
int deleteNode(Node** head, int data)
{
	Node* cur = *head;
	while (cur != NULL && cur->data != data)
		cur = cur->next;
	if (cur == NULL)
		return 0;

	if (cur->prev == NULL)
		*head = cur->next;        /* 目标是头节点，head 后移 */
	else
		cur->prev->next = cur->next; /* 前驱跳过 cur */

	if (cur->next != NULL)
		cur->next->prev = cur->prev; /* 后继跳过 cur */

	free(cur);
	return 1;
}

/* 正向遍历：从 head 沿 next 一路走到 NULL */
void printForward(Node* head)
{
	printf("正向遍历: ");
	Node* cur = head;
	while (cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

/* 反向遍历：先沿 next 走到尾节点，再沿 prev 倒着打印，这是双向链表的优势 */
void printBackward(Node* head)
{
	printf("反向遍历: ");
	Node* cur = head;
	if (cur == NULL)
	{
		printf("\n");
		return;
	}
	while (cur->next != NULL)
		cur = cur->next;           /* 到达尾节点 */
	while (cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->prev;           /* 沿 prev 倒退 */
	}
	printf("\n");
}

/*
 * 释放整条链表
 * 逐个节点保存 next 后再 free 当前节点（直接 free 会丢失后续指针）
 * 最后把 head 置为 NULL，避免野指针
 */
void freeList(Node** head)
{
	Node* cur = *head;
	while (cur != NULL)
	{
		Node* temp = cur;
		cur = cur->next;
		free(temp);
	}
	*head = NULL;
}
