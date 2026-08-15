#include<stdio.h>

/*   方法一：  使用switch语句实现用户的输入 */

int add(int x, int y)
{
	return x + y;
}

int Sub(int x, int y)
{
	return x - y;
}

int Mul(int x, int y)
{
	return x * y;
}

int Div(int x,int y)
{
	return x / y;
}

void menu()
{
	printf("----------------------\n");
	printf("---- 1.add   2.Sub ---\n");
	printf("---- 3.Mul   4.Div ---\n");
	printf("---- 0.exit        ---\n");
	printf("----------------------\n");
}

int main()
{
	int input = 0;
	int x = 0;
	int y = 0;
	int r = 0;
	do 
	{
		menu();
		printf("请选择：");
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
			printf("请输入两个数：");
			scanf_s("%d %d", &x, &y);
			r = add(x, y);
			printf("%d\n", r);
			break;
		case 2:
			printf("请输入两个数：");
			scanf_s("%d %d", &x, &y);
			r = Sub(x, y);
			printf("%d\n", r);
			break;
		case 3:
			printf("请输入两个数：");
			scanf_s("%d %d", &x, &y);
			r = Mul(x, y);
			printf("%d\n", r);
			break;
		case 4:
			printf("请输入两个数：");
			scanf_s("%d %d", &x, &y);
			r = Div(x, y);
			printf("%d\n", r);
			break;
		case 0:
			printf("exit\n");
			break;
		default:
			printf("输入失败\n");
			break;
		}
	} while (input);
	return 0;
}


/*  方法二：   使用指针的知识实现计算器的操作  */
int add(int x, int y)
{
	return x + y;
}

int Sub(int x, int y)
{
	return x - y;
}

int Mul(int x, int y)
{
	return x * y;
}

int Div(int x, int y)
{
	return x / y;
}

void menu()
{
	printf("----------------------\n");
	printf("---- 1.add   2.Sub ---\n");
	printf("---- 3.Mul   4.Div ---\n");
	printf("---- 0.exit        ---\n");
	printf("----------------------\n");
}

int main()
{
	int input = 0;
	int x = 0;
	int y = 0;
	int r = 0;
	int (*p[5])(int x, int y) = {0,add,Sub,Mul,Div};
	do {
		menu();
		printf("请选择：");
		scanf_s("%d", &input);

		if (input <= 4 && input >= 1) 
		{
			printf("请输入两个数：");
			scanf_s("%d %d", &x, &y);
			r = (*p[input])(x, y);
			printf("%d\n", r);
		}
		else if (input == 0) {
			printf("退出计算器\n");
		}
		else {
			printf("输入的有误\n");
		}
	} while (input);
	return 0;
}