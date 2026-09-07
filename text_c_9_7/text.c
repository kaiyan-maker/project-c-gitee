#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

/*  写⼀个函数Strlen，可以求字符串⻓度，注：字符串的结束标志是 \0 .
输⼊⼀个字符串（字符串⻓度⼩于等于30，中间不包含空格），使⽤Strlen函数可以求字符串的⻓
度，并返回  */
int Strlen(const char* str)  // str -> 指向字符串的指针
{
	// 定义一个计数器
	int count = 0;

	// 使用while循环遍历字符串
	while (*str)
	{
		count++;
		 
		str++;  // 字符串指针后移，计数加一
	}

	return count;
}

int main()
{
	char arr[31] = { 0 };
	printf("请输入:");
	scanf("%[^\n]s", &arr);

	// 模拟strlen的用法
	int len = Strlen(arr);

	printf("%d", len);
	return 0;
}

/*  写⼀个函数Strlen，可以求字符串⻓度，除了函数的形参，函数中不能使⽤多余的变量。
输⼊⼀个字符串（字符串⻓度⼩于等于30，中间不包含空格），使⽤Strlen函数可以求字符串的⻓
度，并返回。  */

// 使用函数递归的方法实现
int Strlen(const char* str)
{
	if (*str == '\0')
		return 0;
	return 1 + Strlen(str + 1);
}

int main()
{
	char arr[31] = { 0 };
	printf("请输入：");
	scanf("%[^\n]s", &arr);

	int len = Strlen(arr);

	printf("%d\n", len);
	return 0;
}

/*  输⼊⼀个字符串，写⼀个函数将⼀个字符串的内容逆序过来  */
void reverse(char* str)
{
	// 1.求字符串长度
	int len = (int)strlen(str);
	// 2.定义两个指针变量来表示字符串的首位(末位)元素
	char* left = str;
	char* right = str + len - 1;    // 比如：输入10个元素，str=0;len=10;str+len=11;str+len-1=10

	while (left < right)
	{
		char tmp = *left;
		*left = *right;
		*right = tmp;

		left++;
		right--;
	}
}

int main()
{
	// 定义一个字符数组
	char arr[31] = { 0 };
	// 输入字符串
	printf("请输入：");
	scanf("%[^\n]s", &arr);
	
	// 函数调用
	reverse(arr);

	printf("%s", arr);
	return 0;
}

/*  输⼊⼀个整数m，求这个整数m的每⼀位之和，并打印。  */
int digit_sum(int m)
{
	int sum = 0;
	// 循环遍历每一位数的位数，并加起来
	while (m)
	{
		sum += m % 10;  // 取出最后一位 sum = sum + (m % 10);
		m /= 10;       // 删除最后一位  m = m / 10;
	}

	// 返回每一位的数之和
	return sum;
}

int main()
{
	int m = 0;

	scanf("%d", &m);  // 输入数据

	int ps = digit_sum(m);  // 调用函数
	
	printf("%d", ps);  // 输出数字之和

	return 0;
}