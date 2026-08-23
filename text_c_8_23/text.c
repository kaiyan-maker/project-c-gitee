#include<stdio.h>

	/*   结构体初阶   */
//struct Stu
//{
//	char id[12];
//	char name[13];
//	int age;
//	char sex[5];
//};


//struct S
//{
//	int data[1000];
//	int num;
//};
//
//struct S s = { {1,2,3},1000 };
//
//// 结构体传参
//// void 是无符号整型
//void Print1(struct S s1)
//{
//	printf("%d\n", s1.num);
//}
//
//// 结构体地址传参
//void Print2(struct S* s2)
//{
//	printf("%d\n", s2->data);
//}
//
////struct Stu s1;  // 全局变量
//int main()
//{
//	//struct Stu s = { "2026010101","changsan",20,"男" };   // 局部变量
//	//struct Stu s2 = { .age = 18,.id = "2026010102",.name = "lisi",.sex = "女" };    // 指定顺序初始化
//	//struct Stu s3 = { "wangwu",34 };  // 不完全初始化
//
//	//struct Stu s4 = { 0 };
//	//s4 = s;
//	//struct Stu r = s4;
//
//	//s.age = 30;
//
//	/*   语法：结构体变量.成员名   */
//	//printf("学号：%s\n", s.id);
//	//printf("姓名：%s\n", s.name);
//	//printf("年龄：%d\n", s.age);
//	//printf("性别：%s\n", s.sex);
//
//	/*  语法： 结构体指针.成员名  */
//	//struct Stu* ps = &s;  // 结构体指针
//
//	//printf("name:%s\n", ps->name);
//	//printf("age:%d\n", ps->age);
//	//printf("id:%s\n", ps->id);
//	//printf("sex:%s\n", ps->sex);
//
//
//	Print1(s);  // 传结构体
//	Print2(&s);   // 传地址
//
//	return 0;
//}


/* 结论：结构体传参的时候，要传结构体的地址。*/
#include<string.h>
int main()
{
	// 对于给定的由小写字母和空格混合构成的字符串s,将其翻转后输出。
	// 保证给定的字符串s的首尾不为空格。
	char s[1000];  // 定义一个初始化字符数组
	printf("请输入字符串：");
	fgets(s, sizeof(s), stdin);  // 读取字符数组

	// 去除fgets的"\n"
	size_t len = strlen(s);    // 统计字符的个数
	if (len > 0 && s[len - 1] == "\n")
	{
		s[len - 1] = "\0";
		len--;
	}

	// 翻转字符串
	int left = 0;
	int right = len - 1;

	while (left < right)
	{
		char temp = s[left];
		s[left] = s[right];
		s[right] = temp;
		left++;
		right--;
	}

	printf("反转后的字符串：%s", s);
	return 0;
}