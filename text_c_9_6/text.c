#include<stdio.h>
#include<ctype.h>

/*  输⼊⼀个字符串，将字符串中⼤写字⺟全部转为⼩写字⺟，⼩写字⺟转成⼤写字⺟，其他字符保持不
变。注：字符串的⻓度⼩于等于30，其中字符串中包含空格  */
int main()
{
	char num[31] = { 0 };
	printf("请输入：");
	scanf_s("%s", &num);
	
	int i = 0;

	// 循环遍历这个字符串
	while (num[i])
	{
		if (num[i] >= 'a' && num[i] <= 'z') num[i] -= 32;
		else if (num[i] >= 'A' && num[i] <= 'Z') num[i] += 32;
		else printf("输入错误\n");
	}

	printf("%s\n", num);
	return 0;
}


/*  写⼀个函数Swap，可以交换两个整数的内容。注意必须实现成函数完成。
输⼊2个整数，调⽤⾃定义函数Swap，完成2个整数的交  */

void Swap(int n1,int n2)
{
	int tmp = n1;
	n1 = n2;
	n2 = tmp;
}

 void Swap(int* n1, int* n2)
{
	int tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

int main()
{
	int num1 = 10;
	int num2 = 20;
	//scanf_s("%d %d",&num1,&num2);
	Swap(num1,num2);

	printf("%d %d\n", num1,num2);
	return 0;
}


/*  输⼊2个整数m和n，写⼀个函数average，求2个整数的平均值，考虑整数过⼤溢出的问题。*/

// 方法一：（没有考虑到）
double average(int n,int m)
{
	double res = (double)((m + n) / 2);
	return res;
}

// 方法二：（考虑到溢出的问题）
double average(int n, int m)
{
	return n + (m - n) / 2;
}

int main()
{
	int n = 0;
	int m = 0;
	scanf_s("%d %d", &n, &m);
	double ree = average(n,m);

	printf("%.2f", ree);

	return 0;
}