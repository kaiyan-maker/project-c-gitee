#include "SList.h"

// 链表的打印
SLIST_API void SLTPrint(SLTNode* phead)
{
	SLTNode* cur = phead;
	while (cur != NULL)
	{
		SLIST_PRINT_DATA(cur->data);
		cur = cur->next;
	}
	printf("\n");
}

// 尾部插入：无节点时直接创建头节点，否则遍历到最后一个节点后面插入
SLIST_API void SLTPushBack(SLTNode** pphead, SLDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		printf("malloc failed!\n");
		return;
	}
	newnode->data = x;
	newnode->next = NULL;

	if (*pphead == NULL)
	{
		*pphead = newnode;
		return;
	}

	SLTNode* cur = *pphead;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = newnode;
}

// 头部插入：空链表与非空链表都要让新节点成为新的头节点
SLIST_API void SLTPushFront(SLTNode** pphead, SLDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		printf("malloc failed!\n");
		return;
	}
	newnode->data = x;
	newnode->next = *pphead;
	*pphead = newnode;
}

// 尾部删除：空链表直接返回，只有一个节点时删除头节点，否则删掉最后一个节点
SLIST_API void SLTPopBack(SLTNode** pphead)
{
	if (*pphead == NULL)
	{
		printf("empty list!\n");
		return;
	}

	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
		return;
	}

	SLTNode* cur = *pphead;
	while (cur->next->next != NULL)
	{
		cur = cur->next;
	}
	free(cur->next);
	cur->next = NULL;
}

// 头部删除：空链表直接返回，否则让头节点指向它的下一个节点
SLIST_API void SLTPopFront(SLTNode** pphead)
{
	if (*pphead == NULL)
	{
		printf("empty list!\n");
		return;
	}

	SLTNode* node = *pphead;
	*pphead = (*pphead)->next;
	free(node);
}

// 查找：找到返回该节点的地址，找不到返回 NULL
SLIST_API SLTNode* SLTFind(SLTNode* phead, SLDataType x)
{
	SLTNode* cur = phead;
	while (cur != NULL)
	{
		if (SLIST_CMP_DATA(cur->data, x))
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

// 在 pos 节点之前插入数据：pos 为头节点时按头部插入处理，pos 为 NULL 时按头部插入处理
SLIST_API void SLTInsert(SLTNode** pphead, SLTNode* pos, SLDataType x)
{
	if (pos == NULL)
	{
		SLTPushFront(pphead, x);
		return;
	}

	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		printf("malloc failed!\n");
		return;
	}
	newnode->data = x;
	newnode->next = pos;

	if (*pphead == pos)
	{
		// pos 就是头节点，新节点成为新的头节点
		*pphead = newnode;
		return;
	}

	// 遍历找到 pos 的前驱节点
	SLTNode* cur = *pphead;
	while (cur->next != pos)
	{
		cur = cur->next;
	}
	cur->next = newnode;
}

// 删除 pos 节点：pos 为头节点时按头部删除处理，pos 为 NULL 直接返回
SLIST_API void SLTErase(SLTNode** pphead, SLTNode* pos)
{
	if (*pphead == NULL || pos == NULL)
	{
		printf("cannot erase!\n");
		return;
	}

	if (*pphead == pos)
	{
		SLTPopFront(pphead);
		return;
	}

	// 遍历找到 pos 的前驱节点
	SLTNode* cur = *pphead;
	while (cur->next != pos)
	{
		cur = cur->next;
	}
	cur->next = pos->next;
	free(pos);
}

// 在 pos 节点之后插入数据：新节点插入到 pos 和 pos->next 之间
SLIST_API void SLTInsertAfter(SLTNode* pos, SLDataType x)
{
	if (pos == NULL)
	{
		return;
	}

	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		printf("malloc failed!\n");
		return;
	}
	newnode->data = x;
	newnode->next = pos->next;
	pos->next = newnode;
}

// 删除 pos 之后的节点：pos 为 NULL 或 pos 已经是最后一个节点时不做任何事
SLIST_API void SLTEraseAfter(SLTNode* pos)
{
	if (pos == NULL || pos->next == NULL)
	{
		return;
	}

	SLTNode* node = pos->next;
	pos->next = node->next;
	free(node);
}

// 销毁链表：逐个释放节点，最后把头指针置空
SLIST_API void SListDesTroy(SLTNode** pphead)
{
	SLTNode* cur = *pphead;
	while (cur != NULL)
	{
		SLTNode* node = cur;
		cur = cur->next;
		free(node);
	}
	*pphead = NULL;
}