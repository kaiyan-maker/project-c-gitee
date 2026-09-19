// Contact.c - 通讯录功能的实现
#define  _CRT_SECURE_NO_WARNINGS 1  // 关闭 scanf 等不安全函数的安全警告
#include "Contact.h"
#include "SeqList.h"

// 通讯录的初始化
// 通讯录底层就是顺序表，所以直接调用顺序表的初始化即可
void ContactInit(Contact* con)
{
	SLInit(con);
}

// 通讯录的销毁
// 顺序表销毁时会释放堆区内存，通讯录随之销毁
void ContactDesTroy(Contact* con)
{
	SLDestroy(con);
}

// 通讯录的添加数据
// 步骤：录入联系人信息 -> 尾插到顺序表末尾
void ContactAdd(Contact* con)
{
	// 获取用户输入的内容
	peoInfo info;  // 先定义一个新的联系人变量
	printf("请输入添加的姓名：\n");
	scanf("%s", info.name);  // 姓名是数组，数组名本身就是地址，不用取地址

	printf("请输入添加的性别：\n");
	scanf("%s", info.gender);

	printf("请输入添加的年龄：\n");
	scanf("%d", &info.age);  // 整型变量需要取地址

	printf("请输入添加的电话：\n");
	scanf("%s", info.tel);

	printf("请输入添加的住址：\n");
	scanf("%s", info.addr);

	// 往通讯录里添加联系人数据
	SLPushBack(con, info);  // 尾插：把整个联系人结构体存进顺序表
}

// 按姓名查找联系人（内部工具函数）
// 参数 con：通讯录；name：要查找的姓名
// 返回值：找到返回下标，没找到返回 -1
int FindByName(Contact* con, char name[])
{
	// 从头到尾遍历通讯录
	for (int i = 0;i < con->size;i++)
	{
		// strcmp：比较两个字符串是否相等，返回 0 表示相等
		if (0 == strcmp(con->arr[i].name, name))
		{
			// 找到了
			return i;
		}
	}
	// 没找到
	return -1;
}

// 通讯录的删除数据
// 步骤：输入姓名 -> 查找 -> 存在才删除
void ContactDel(Contact* con)
{
	// 要删除的数据必须要存在，才能执行删除操作
	// 查找
	char name[NAME_MAX];
	printf("请输入要删除的联系人：\n");
	scanf("%s", name);
	int find = FindByName(con, name);  // 先按姓名查找
	if (find < 0)  // 返回 -1 说明不存在
	{
		printf("要删除的联系人数据不存在\n");
		return;
	}
	// 要删除的联系人存在
	SLErase(con, find);  // 删除该位置的联系人
	printf("删除成功\n");
}

// 展示通讯录数据
// 作用：打印表头，然后遍历打印所有联系人
void ContactShow(Contact* con)
{
	printf("%s %s %s %s %s\n", "姓名", "性别", "年龄", "电话", "地址");
	// 遍历通讯录
	for (int i = 0;i < con->size;i++)
	{
		printf("%s %s %d %s %s\n",
			con->arr[i].name,
			con->arr[i].gender,
			con->arr[i].age,
			con->arr[i].tel,
			con->arr[i].addr
		);
	}
}

// 通讯录的修改数据
// 步骤：输入姓名 -> 查找 -> 存在则重新录入全部信息
void ContactModify(Contact* con)
{
	// 要修改的联系人的数据存在
	char name[NAME_MAX];
	printf("要修改的联系人的姓名：\n");
	scanf("%s", name);

	int find = FindByName(con, name);  // 先按姓名定位到要修改的联系人
	if (find < 0)
	{
		printf("要修改的联系人的数据不存在\n");
		return;
	}
	// 直接修改：用新输入的内容覆盖原来的数据
	printf("请输入要修改的姓名：\n");
	scanf("%s", con->arr[find].name);

	printf("请输入要修改的性别：\n");
	scanf("%s", con->arr[find].gender);

	printf("请输入要修改的年龄：\n");
	scanf("%d", &con->arr[find].age);

	printf("请输入要修改的电话：\n");
	scanf("%s", con->arr[find].tel);

	printf("请输入要修改的住址：\n");
	scanf("%s", con->arr[find].addr);

	printf("修改成功!\n");
}

// 通讯录的查找数据
// 步骤：输入姓名 -> 查找 -> 存在则打印该联系人的信息
void ContactFind(Contact* con)
{
	char name[NAME_MAX];
	printf("请输入要查找的联系人的姓名：\n");
	scanf("%s", name);

	int find = FindByName(con, name);  // 按姓名查找
	if (find < 0)
	{
		printf("要查找的联系人的数据不存在\n");
		return;
	}

	printf("%s %s %s %s %s\n", "姓名", "性别", "年龄", "电话", "地址");
	// 打印该联系人的信息
	printf("%3s %3s %3d %3s %3s\n",
		con->arr[find].name,
		con->arr[find].gender,
		con->arr[find].age,
		con->arr[find].tel,
		con->arr[find].addr
	);
}