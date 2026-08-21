#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>


int Add(int x, int y)
{
	return (x + y) / 2;
}

int Max(int x, int y)
{
	return (x > y ? x : y);
}

void set_arr(int arr[],int sz)
{
	for (int i = 0;i < sz;i++)
	{
		arr[i] = -1;
	}
}

void print_arr(int arr[],int sz)
{
	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int is_leap_year(int y)
{
	if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
		return 1;
	else
		return 0;
}

int get_days_month(int y, int m)
{
	if (m < 1 || m > 12)
		return -1;
	int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int day = days[m];
	if (is_leap_year(y) && m == 2)
		day += 1;
	return day;
}

//int main()
//{
//	// 写⼀个函数，计算2个整型变量的平均，按照整数除法计算
//	
//	int num1 = 4;
//	int num2 = 2;
//	//int r = Add(num1, num2);
//
//	//printf("%d\n", r);
//	
//	// 写⼀个函数求2个整数的较⼤值
//	//int r = Max(num1, num2);
//	//printf("%d\n", r);
//
//	// 写⼀个函数将⼀个整型数组的内容，全部置为-1，再写⼀个函数打印数组的内容。
//	//int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
//	//int sz = sizeof(arr) / sizeof(arr[0]);
//	//set_arr(arr,sz);  // 设置数组内容为-1
//	//print_arr(arr,sz);  // 打印数组内容
//	
//	//int y = 0;
//	//int m = 0;
//	//scanf("%d %d", &y, &m);
//	//int d = get_days_month(y, m);
//	//printf("%d\n", d);
//	
//	return 0;
//}

#include<string.h>

int is_leap_year(int y)
{
	if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
	{
		return 1;
	}
	else
		return 0;
}
int main()
{
	//int len = strlen("abcdef");
	//printf("%d\n", len);
	
	//printf("%d\n", strlen("abcdef")); // 链式访问
	//printf("%d", printf("%d", printf("%d", 43)));

	// 我们要写⼀个函数判断⼀年是否是闰年。
	int y = 0;
	scanf("%d", &y);
	int r = is_leap_year(y);

	if (r == 1)
		printf("闰年");
	else
		printf("平年");
	return 0;
}

static int g_val = 20;  // 私有成员变量
int main()
{
	// 函数的定义也是一种特殊的声明
	// 函数的调用一定要满足，先声明后使用
	
	// static 静态的  （修饰局部变量，全局变量，函数）
	// extern  用来声明外部符号的
	printf("%d", g_val);
	return 0;
}

int Frb(int n)
{
	if (n == 0)
		return 1;
	return n * Frb(n - 1);
}

int main()
{
	// 计算正整数n的阶乘
	int n = 0;
	printf("请选择：");
	scanf("%d", &n);
	int r = Frb(n);

	printf("%d", r);
	return 0;
}

void Frb(int m)
{
	if (m > 9)
		Frb(m / 10);
	printf("%d ", m % 10);
}

int main()
{
	// 输入一个正整数m,按照顺序打印整数的每一位
	int m = 0;
	scanf("%d", &m);
	Frb(m);

	return 0;
}

int Frb(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	return Frb(n - 1) + Frb(n - 2);
}
int main()
{
	// 计算裴波纳契数
	int n = 0;
	scanf("%d", &n);

	int r = Frb(n);

	printf("%d", r);
	return 0;
}

int count = 0;
void test()
{
	count++;
	printf("当前深度：%d\n", count);
	int buffer[1000] = { 0 };  // 占用栈空间
	test();  // 无限递归
}
int main()
{
	test(); 
	
	return 0;
}

int Frb(int n)
{
	int a = 0;
	int b = 0;
	int c = 0;
	while (n > 2)
	{
		c = a + b;
		a = b;
		b = c;
		n--;
	}
	return c;
}
int main()
{
	int n = 0;
	scanf("%d", &n);
	int r = Frb(n);
	printf("%d", r);
	return 0;
}


// 尾递归
long long Fac(int n, long long acc)
{
	if (n <= 1) return acc;
	return Fac(n - 1, n * acc);
}

long long Fac(int n)
{
	if (n < 0) return -1;
	return Fac(n, 1);
}
int main()
{
	int n = 0;
	int acc = 0;
	scanf("%d %d", &n,&acc);
	Fac(n, acc);
	return 0;
}



// 递归⼆分查找函数
// arr: 有序数组（升序）
// left: 左边界索引
// right: 右边界索引
// target: 要查找的⽬标值
// 返回值: 找到返回索引，未找到返回-1
int binarySearch(int arr[], int left, int right, int targht)
{
	if (left > right)
		return -1;
	// 计算中间索引（避免溢出）
	int mid = left + (right - left) / 2;

	if (arr[mid] == targht)  // 找到目标值
		return mid;
	else if (arr[mid] > targht)  // 目标值在左半部分
		return binarySearch(arr, left, mid - 1, targht);
	else  // 目标值在右半部分
		return binarySearch(arr, mid + 1, right, targht);
}

// 包装函数，简化调用
int search(int arr[],int sz,int targht)
{
	return binarySearch(arr, 0, sz - 1, targht);
}
int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int left = 0;
	int right = sizeof(arr) / sizeof(arr[0]) - 1;
	int targht;

	printf("有序数组：");
	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	// 测试查找
	targht = 7;
	int result = search(arr, sz, targht);
	if (result != -1)
	{
		printf("元素 %d 找到，索引为： %d\n", targht, result);
	}
	else {
		printf("元素 %d 未找到", targht);
	}

	targht = 10;
	result = search(arr, sz, targht);
	if (result != -1)
	{
		printf("元素 %d 找到，索引为：%d\n", targht, result);
	}
	else {
		printf("元素 %d 未找到\n", targht);
	}
	return 0;
}