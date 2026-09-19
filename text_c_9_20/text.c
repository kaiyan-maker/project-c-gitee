// text.c - 程序的主入口（main 函数所在地），负责整个游戏/程序的驱动
// 里面还有一些顺序表和通讯录的测试代码，已被注释掉，仅供参考
#define _CRT_SECURE_NO_WARNINGS 1  // 关闭 scanf 等不安全函数的安全警告
#include "SeqList.h"  // 包含了顺序表和通讯录的接口

/*void SLTest01()
{
	SL sl;
	SLInit(&sl);
	// 测试尾插
	SLPushBack(&sl,1);
	SLPushBack(&sl,2);
	SLPushBack(&sl,3);
	SLPrint(sl);

	//SLPushFront(&sl,4);
	//SLPushFront(&sl,5);

	// 测试尾删
	//SLPopBack(&sl);
	//SLPrint(sl);
	//SLPopBack(&sl);
	//SLPrint(sl);
	//SLPopBack(&sl);
	//SLPrint(sl);
	//SLPopBack(&sl);
	//SLPrint(sl);
	
	// 测试头删
	//SLPopFront(&sl);
	//SLPrint(sl);
	//SLPopFront(&sl);
	//SLPrint(sl);
	//SLPopFront(&sl);
	//SLPrint(sl);
	//SLPopFront(&sl);
	SLPrint(sl);
	SLDestroy(&sl);
}

void SLTest02()
{
	SL sl;
	SLInit(&sl);

	SLPushBack(&sl, 1);
	SLPushBack(&sl, 2);
	SLPushBack(&sl, 3);
	SLPrint(sl);

	//SLInSert(&sl, 1, 99);
	//SLInSert(&sl, sl.size, 88);
	
	//SLErase(&sl, 0);
	//SLPrint(sl);

	int find = SLFind(&sl, 2);
	if (find < 0)
	{
		printf("未找到\n");
	}
	else {
		printf("找到了，下标为%d\n", find);
	}
	SLDestroy(&sl);
}*/

//void ContactTest01()
//{
//	Contact con;  // 创建的通讯录对象，实际是 顺序表的对象，--> sl
//	ContactInit(&con);
//	ContactAdd(&con);
//	ContactDesTroy(&con);  // 通讯录的销毁
//}

// 菜单函数：打印操作选项供用户选择
void menu()
{
	printf("****** 通讯录 *******\n");
	printf("****    1.add    ****\n");
	printf("****    2.del    ****\n");
	printf("****    3.mod    ****\n");
	printf("****    4.find   ****\n");
	printf("****    5.show   ****\n");
	printf("****    0.exit   ****\n");
	printf("********************\n");

}

// 主函数：通讯录的主循环
// 思路：初始化通讯录 -> 循环弹菜单让用户选择 -> 按选项执行对应功能 -> 直到输入 0 退出
int main()
{
	int op = -1;  // 用户输入的选项，初始化为 -1
	Contact con;  // 创建通讯录对象
	ContactInit(&con);  // 初始化通讯录
	do
	{
		menu();  // 打印菜单
		printf("请选择你的操作:");
		scanf("%d", &op);  // 读取用户输入的操作编号

		switch (op)  // 根据用户选择执行对应功能
		{
		case 1:
			ContactAdd(&con);  // 添加联系人
			break;
		case 2:
			ContactDel(&con);  // 删除联系人
			break;
		case 3:
			ContactModify(&con);  // 修改联系人
			break;
		case 4:
			ContactFind(&con);  // 查找联系人
			break;
		case 5:
			ContactShow(&con);  // 展示所有联系人
			break;
		case 0:
			printf("退出通讯录。。。\n");  // 退出
			break;
		default:
			break;  // 输入其它数字则忽略，继续循环
		}
	} while (op != 0);  // 用户输入 0 时退出循环

	ContactDesTroy(&con);  // 退出前销毁通讯录，释放内存
	return 0;
}