#define _CRT_SECURE_NO_WARNINGS
#include"contact.h"

/* ---------------------------------------------------------------------------
   模板复用：在包含 SList.c 之前用宏把数据域类型换成 PeoInfo、节点类型换成
   contact，这样通讯录就能直接复用 SList 的链表接口，不必重复实现一遍。
   函数名也要全部改名，否则会与 SList.c 里 int 版本的那份实现链接冲突；
   再定义 SLIST_STATIC，让这一份实例只服务于 contact.c 内部。
   --------------------------------------------------------------------------- */
#define SLIST_STATIC
#define SLIST_TYPE  PeoInfo
#define SLIST_PRINT_DATA(data) printf("%-10s %-4s %-4d %15s %-20s\n", \
	(data).name, (data).sex, (data).age, (data).tel, (data).addr)
#define SLIST_CMP_DATA(data, x) (strcmp((data).name, (x).name) == 0)

#define SLTNode        contact
#define SLTPrint       ContactPrint
#define SLTPushBack    ContactPushBack
#define SLTPushFront   ContactPushFront
#define SLTPopBack     ContactPopBack
#define SLTPopFront    ContactPopFront
#define SLTFind        ContactFind
#define SLTInsert      ContactInsert
#define SLTErase       ContactErase
#define SLTInsertAfter ContactInsertAfter
#define SLTEraseAfter  ContactEraseAfter
#define SListDesTroy   ContactDesTroy

#include"SList.c"

/* 读取指定字段并做长度限制。
   逐字符读并丢弃超长部分，这样即使一行超过字段容量，也不会把剩余内容
   留在输入流里导致后续字段全部错位（fgets 就会出这个问题）。 */
static void InputString(const char* tip, char* str, int size)
{
	int ch;
	int n = 0;

	printf("%s", tip);
	fflush(stdout);
	while ((ch = getchar()) != '\n' && ch != EOF)
	{
		if (n < size - 1)
		{
			str[n++] = (char)ch;
		}
	}
	str[n] = '\0';
}

// 读取整数，非法输入按 0 处理
static void InputInt(const char* tip, int* num)
{
	char buf[NUMBER_MAX];
	InputString(tip, buf, NUMBER_MAX);
	*num = atoi(buf);
}

// 把本地的通讯录数据导入到链表结构中
static void LoadContact(contact** con)
{
	FILE* pf = fopen("contact.txt", "rb");
	if (pf == NULL)
	{
		perror("fopen");
		return;
	}

	//循环读取文件数据
	PeoInfo info;
	while (fread(&info, sizeof(info), 1, pf) == 1)
	{
		ContactPushBack(con, info);
	}
	fclose(pf);

	printf("历史数据导入通讯录成功！\n");
}

// 初始化通讯录
void InitContact(contact** con)
{
	*con = NULL;
	LoadContact(con);//把本地的通讯录数据导入到链表结构
}

// 添加通讯录数据（尾插）
void AddContact(contact** con)
{
	PeoInfo info;
	memset(&info, 0, sizeof(info));
	InputString("请输入姓名：", info.name, NAME_MAX);
	InputString("请输入性别：", info.sex, SEX_MAX);
	InputInt("请输入年龄：", &info.age);
	InputString("请输入联系电话：", info.tel, TEL_MAX);
	InputString("请输入地址：", info.addr, ADDR_MAX);

	ContactPushBack(con, info);
	printf("插入成功！\n");
}

// 按姓名查找用户，命中返回该节点地址，否则返回 NULL
// 复用实例化出来的 ContactFind：比较方式由 SLIST_CMP_DATA 决定，即按姓名匹配
static contact* FindByName(contact* con, const char* name)
{
	PeoInfo key;
	memset(&key, 0, sizeof(key));
	strncpy(key.name, name, NAME_MAX - 1);

	return ContactFind(con, key);
}

// 清空通讯录（不落盘）
static void ClearContact(contact** con)
{
	while (*con != NULL)
	{
		ContactPopFront(con);
	}
	printf("通讯录已清空！\n");
}

// 删除通讯录数据
void DelContact(contact** con)
{
	char name[NAME_MAX];
	InputString("请输入要删除的用户姓名：", name, NAME_MAX);

	contact* pos = FindByName(*con, name);
	if (pos == NULL)
	{
		printf("要删除的用户不存在，删除失败！\n");
		return;
	}

	ContactErase(con, pos);
	printf("删除成功！\n");
}

// 展示通讯录数据
void ShowContact(contact* con)
{
	printf("%-10s %-4s %-4s %15s %-20s\n", "姓名", "性别", "年龄", "联系电话", "地址");

	contact* cur = con;
	while (cur != NULL)
	{
		SLIST_PRINT_DATA(cur->data);
		cur = cur->next;
	}
}

// 查找通讯录数据
void FindContact(contact* con)
{
	char name[NAME_MAX];
	InputString("请输入要查找的用户姓名：", name, NAME_MAX);

	contact* pos = FindByName(con, name);
	if (pos == NULL)
	{
		printf("要查找的用户不存在，查找失败！\n");
		return;
	}

	printf("查找成功！\n");
	SLIST_PRINT_DATA(pos->data);
}

// 修改通讯录数据
void ModifyContact(contact** con)
{
	char name[NAME_MAX];
	InputString("请输入要修改的用户名称：", name, NAME_MAX);

	contact* pos = FindByName(*con, name);
	if (pos == NULL)
	{
		printf("要查找的用户不存在，修改失败！\n");
		return;
	}

	InputString("请输入要修改的姓名：", pos->data.name, NAME_MAX);
	InputString("请输入要修改的性别：", pos->data.sex, SEX_MAX);
	InputInt("请输入要修改的年龄：", &pos->data.age);
	InputString("请输入要修改的联系电话：", pos->data.tel, TEL_MAX);
	InputString("请输入要修改的地址：", pos->data.addr, ADDR_MAX);

	printf("修改成功！\n");
}

// 把通讯录数据写入本地文件 contact.txt
static void SaveContact(contact* con)
{
	FILE* pf = fopen("contact.txt", "wb");
	if (pf == NULL)
	{
		perror("fopen");
		return;
	}

	//将通讯录数据写入文件
	contact* cur = con;
	while (cur != NULL)
	{
		fwrite(&(cur->data), sizeof(cur->data), 1, pf);
		cur = cur->next;
	}
	fclose(pf);

	printf("通讯录数据保存成功！\n");
}

// 销毁通讯录数据
void DestroyContact(contact** con)
{
	//在通讯录销毁之前，先把历史数据保存到本地文件中contact.txt
	SaveContact(*con);
	ContactDesTroy(con);
}

// 通讯录菜单
void ContactMenu(void)
{
	contact* con = NULL;
	char choice[NUMBER_MAX];

	InitContact(&con);
	printf("\n");
	ShowContact(con);

	while (1)
	{
		printf("\n");
		printf("===== 通讯录 =====\n");
		printf("1. 新增\n");
		printf("2. 删除\n");
		printf("3. 修改\n");
		printf("4. 查找\n");
		printf("5. 展示\n");
		printf("6. 清空\n");
		printf("0. 退出\n");
		printf("请选择：");
		fflush(stdout);
		if (fgets(choice, NUMBER_MAX, stdin) == NULL)
		{
			break;
		}
		choice[strcspn(choice, "\r\n")] = '\0';

		switch (choice[0])
		{
		case '1':
			AddContact(&con);
			ShowContact(con);
			break;
		case '2':
			DelContact(&con);
			ShowContact(con);
			break;
		case '3':
			ModifyContact(&con);
			ShowContact(con);
			break;
		case '4':
			FindContact(con);
			break;
		case '5':
			ShowContact(con);
			break;
		case '6':
			ClearContact(&con);
			ShowContact(con);
			break;
		case '0':
			DestroyContact(&con);
			printf("通讯录数据已保存到 contact.txt，再见！\n");
			return;
		default:
			printf("无效的选项，请重新输入！\n");
			break;
		}
	}
}