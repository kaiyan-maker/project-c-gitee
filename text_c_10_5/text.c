#include "SList.h"
#include "contact.h"

static void TestPushPop(void)
{
	SLTNode* plist = NULL;
	printf("--- PushBack / PushFront ---\n");
	SLTPushBack(&plist, 1);
	SLTPushBack(&plist, 2);
	SLTPushBack(&plist, 3);
	SLTPrint(plist);          // 1 2 3

	SLTPushFront(&plist, 0);
	SLTPrint(plist);          // 0 1 2 3

	printf("--- PopBack ---\n");
	SLTPopBack(&plist);
	SLTPrint(plist);          // 0 1 2
	SLTPopBack(&plist);
	SLTPopBack(&plist);
	SLTPrint(plist);          // 0
	SLTPopBack(&plist);
	SLTPrint(plist);          // 空表
	SLTPopBack(&plist);       // 对空表删除，应提示 empty list

	printf("--- PopFront ---\n");
	SLTPushBack(&plist, 10);
	SLTPushBack(&plist, 20);
	SLTPushBack(&plist, 30);
	SLTPrint(plist);          // 10 20 30
	SLTPopFront(&plist);
	SLTPrint(plist);          // 20 30
	SLTPopFront(&plist);
	SLTPopFront(&plist);
	SLTPrint(plist);          // 空表
	SLTPopFront(&plist);      // 对空表删除，应提示 empty list

	SListDesTroy(&plist);
	printf("destroy: %s\n\n", plist == NULL ? "NULL" : "not NULL");
}

static void TestFind(void)
{
	SLTNode* plist = NULL;
	int i;
	printf("--- Find ---\n");
	for (i = 1; i <= 5; i++)
	{
		SLTPushBack(&plist, i * 10);
	}
	SLTPrint(plist);                                   // 10 20 30 40 50

	SLTNode* pos = SLTFind(plist, 30);
	printf("find 30: %s\n", pos == NULL ? "NULL" : "found");
	if (pos != NULL)
	{
		SLTInsertAfter(pos, 35);
		SLTPrint(plist);                               // 10 20 30 35 40 50
		SLTEraseAfter(pos);
		SLTPrint(plist);                               // 10 20 30 40 50
	}

	pos = SLTFind(plist, 999);
	printf("find 999: %s\n\n", pos == NULL ? "NULL" : "found");

	SListDesTroy(&plist);
}

static void TestInsert(void)
{
	SLTNode* plist = NULL;
	int i;
	printf("--- Insert(pos 之前) ---\n");
	for (i = 1; i <= 4; i++)
	{
		SLTPushBack(&plist, i);           // 1 2 3 4
	}
	SLTPrint(plist);

	// 在尾节点之前插入
	SLTInsert(&plist, SLTFind(plist, 4), 35);
	SLTPrint(plist);                      // 1 2 3 35 4

	// 在中间节点之前插入
	SLTInsert(&plist, SLTFind(plist, 2), 15);
	SLTPrint(plist);                      // 1 15 2 3 35 4

	// 在头节点之前插入
	SLTInsert(&plist, SLTFind(plist, 1), 0);
	SLTPrint(plist);                      // 0 1 15 2 3 35 4

	// pos 为 NULL 时按头部插入处理
	SLTInsert(&plist, NULL, 99);
	SLTPrint(plist);                      // 99 0 1 15 2 3 35 4

	// 在空链表上按头部插入
	SListDesTroy(&plist);
	SLTInsert(&plist, NULL, 7);
	SLTPrint(plist);                      // 7
	printf("\n");

	SListDesTroy(&plist);
}

static void TestErase(void)
{
	SLTNode* plist = NULL;
	int i;
	printf("--- Erase(pos 节点) ---\n");
	for (i = 1; i <= 5; i++)
	{
		SLTPushBack(&plist, i);           // 1 2 3 4 5
	}

	SLTErase(&plist, SLTFind(plist, 3));  // 1 2 4 5
	SLTPrint(plist);

	SLTErase(&plist, SLTFind(plist, 1));  // 头节点被删
	SLTPrint(plist);                      // 2 4 5

	SLTErase(&plist, SLTFind(plist, 5));  // 尾节点被删
	SLTPrint(plist);                      // 2 4

	SLTErase(&plist, NULL);               // 应提示 cannot erase
	SLTPrint(plist);

	SLTErase(&plist, plist);              // 删除头节点后链表变空
	SLTPrint(plist);
	printf("\n");

	SListDesTroy(&plist);
}

static void TestEraseAfter(void)
{
	SLTNode* plist = NULL;
	int i;
	printf("--- EraseAfter(pos 之后的节点) ---\n");
	for (i = 1; i <= 4; i++)
	{
		SLTPushBack(&plist, i);           // 1 2 3 4
	}

	SLTEraseAfter(SLTFind(plist, 2));    // 1 2 4
	SLTPrint(plist);

	SLTEraseAfter(SLTFind(plist, 4));    // 尾节点后面没有节点
	SLTPrint(plist);                      // 1 2 4

	SLTEraseAfter(NULL);                 // 应无任何影响
	SLTPrint(plist);
	printf("\n");

	SListDesTroy(&plist);
}

int main()
{
	//printf("SList test start\n\n");

	//// 先跑一遍 SList 自身的测试用例，再进入通讯录菜单
	//TestPushPop();
	//TestFind();
	//TestInsert();
	//TestErase();
	//TestEraseAfter();
	//printf("all tests done\n");

	ContactMenu();

	return 0;
}