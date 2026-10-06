#include<stdio.h>
#include"list.h"

/* 双向链表演示程序 */
int main()
{
	Node* head = createList();   /* 创建空链表 */

	/* 尾插 10、20、30，再头插 5，得到 5 10 20 30 */
	pushBack(&head, 10);
	pushBack(&head, 20);
	pushBack(&head, 30);
	pushFront(&head, 5);
	printForward(head);
	printBackward(head);

	/* 在第 1 个节点（值 10）之后插入 15，得到 5 10 15 20 30 */
	if (insertAfter(head, 1, 15))
		printf("插入成功\n");
	printForward(head);

	/* 删除值为 20 的节点，得到 5 10 15 30 */
	if (deleteNode(&head, 20))
		printf("删除成功\n");
	printForward(head);
	printBackward(head);

	freeList(&head);             /* 释放全部节点，防止内存泄漏 */
	return 0;
}
