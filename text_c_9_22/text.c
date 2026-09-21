#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

void emun()
{
	printf("==================================\n");
	printf("=====  1.add          2.sub  =====\n");
	printf("=====  3.mul          4.div  =====\n");
	printf("=====          0.exit        =====\n");
	printf("==================================\n");
}

int Add(int a,int b)
{
	return a + b;
}

int Sub(int a,int b)
{
	return a - b;
}

int Mul(int a,int b)
{
	return a * b;
}

int Div(int a,int b)
{
	return a / b;
}

int main()
{
	int input = 0;
	int num1 = 0;
	int num2 = 0;
	do
	{
		emun();
		printf("请输入您要选择的选项：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("请输入两个数：");
			scanf("%d %d", &num1, &num2);
			int p1 = Add(num1,num2);
			printf("已算出！算出的结果：%d\n", p1);
			break;
		case 2:
			printf("请输入两个数：");
			scanf("%d %d", &num1, &num2);
			int p2 = Sub(num1,num2);
			printf("已算出！算出的结果：%d\n", p2);
			break;
		case 3:
			printf("请输入两个数：");
			scanf("%d %d", &num1, &num2);
			int p3 = Mul(num1,num2);
			printf("已算出！算出的结果：%d\n", p3);
			break;
		case 4:
			printf("请输入两个数：");
			scanf("%d %d", &num1, &num2);
			int p4 = Div(num1,num2);
			printf("已算出！算出的结果：%d\n", p4);
			break;
		case 0:
			printf("正在退出。。。");
			break;
		default:
			printf("您输入错误，请重新输入\n");
			break;
		}
	} while (input);

	return 0;
}