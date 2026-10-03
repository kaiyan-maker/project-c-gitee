#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX_TRY 5
#define MAX_MIN 100

void menu()
{
	printf("============================\n");
	printf("===  1. add     0. exit  ===\n");
	printf("============================\n");
}

void Guess_Number()
{
	int r = rand() % MAX_MIN + 1;
	int guess = 0;
	int used = 0;
	int ok = 0;
	int c = 0;
	time_t start = time(NULL);

	printf("游戏开始！答案在 1 ~ 100 之间，你有 %d 次机会\n", MAX_TRY);
	while (used < MAX_TRY)
	{
		ok = 0;
		while (!ok)
		{
			printf("请输入要猜的数字：");
			if (scanf_s("%d", &guess) != 1 || guess < 1 || guess > MAX_MIN)
			{
				printf("输入无效，请输入 1 ~ 100 之间的整数。\n");
			}
			else
			{
				ok = 1;
			}
			while ((c = getchar()) != '\n' && c != EOF)
			{
				;
			}
			if (c == EOF)
			{
				printf("\n输入结束，游戏退出。\n");
				return;
			}
		}

		used++;
		printf("已用时：%ld秒，剩余次数：%d\n", (long)difftime(time(NULL), start), MAX_TRY - used);

		if (guess > r)
		{
			printf("猜大了\n");
		}
		else if (guess < r)
		{
			printf("猜小了\n");
		}
		else
		{
			printf("恭喜你，猜对了，猜出来的数字：%d\n",guess);
			printf("一共猜了 %d 次，总用时：%ld秒\n", used, (long)difftime(time(NULL), start));
			break;
		}
	}

	if (used >= MAX_TRY && guess != r)
	{
		printf("游戏失败！你已经用完 %d 次机会。\n", MAX_TRY);
		printf("正确答案是：%d\n", r);
		printf("总用时：%ld秒\n", (long)difftime(time(NULL), start));
	}
}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请输入要输入的选项：");
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
			Guess_Number();
			break;
		case 0:
			printf("退出中。。。\n");
			break;
		default:
			printf("输入有误\n");
			break;
		}
	} while (input);
	return 0;
}