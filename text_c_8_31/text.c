#include<stdio.h>

/*  打印 1~100之间的奇数  */
int main()
{
	for (int i = 1;i <= 100;i++)
	{
		if (i % 2 == 1)
		{
			printf("奇数%d:\n",i);
		}
		else {
			printf("偶数%d:\n",i);
		}
	}
	return 0;
}

/*  使⽤C语⾔写⼀个程序打印9*9乘法⼝诀表  */
int main()
{
	for (int i = 1;i <= 9;i++)
	{
		for (int j = 1;j <= i;j++)
		{
			printf("%d*%d=%d ", j, i, j * i);
		}
		printf("\n");
	}
	return 0;
}

/*  使⽤C语⾔写⼀个程序打印100~200之间的素数，数字中间使⽤空格分割。 */
int main()
{
	for (int i = 100;i <= 200;i++)
	{
		int flag = 1;
		for (int j = 2;j < i;j++)
		{
			if (i % j == 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1) 
		{
			printf("%d ", i);
		}
	}
	return 0;
}

/*  输⼊三个整数a,b,c，判断由a,b,c作为三条边组成的三⻆形，如果不能组成三⻆形则输出：⾮三⻆
形；如果是三⻆形，再继续判断，如果是等边三⻆形，则输出：等边三⻆形；如果是等腰三⻆形，则
输出：等腰三⻆形；否则输出普通三⻆形。  */
int main()
{
	int a = 0, b = 0, c = 0;
	int* p1 = &a;
	int* p2 = &b;
	int* p3 = &c;
	printf("请输入：");
	scanf_s("%d %d %d", &a, &b, &c);

	if (a + b > c && a + c > b && b + c > a)
	{
		if (a == b && b == c)
		{
			printf("等边三角形\n");
		}
		else if (a == b || b == c || a == c)
		{
			printf("等腰三角形\n");
		}
		else if (((*p1) * (*p2) == (*p3)) || ((*p1) * (*p3) == (*p2)) || ((*p2) * (*p3) == (*p1)))
		{
			printf("直角三角形\n");
		}
		else
		{
			printf("普通三角形\n");
		}
	}
	else
	{
		printf("非三角形\n");
	}
	return 0;
}