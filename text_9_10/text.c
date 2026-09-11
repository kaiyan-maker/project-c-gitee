#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

/*  猜数字小游戏  */
void enmu()
{
	printf("==================\n");
	printf("===  1. play   ===\n");
	printf("===  0.exit    ===\n");
	printf("==================\n");
}

void play_input()
{
	int r = rand() % 100 + 1; // 设置1-100的随机数
	int guess = 0;
	int count = 0;  // 设置一个计数器
	// 1.记下开始时的数
	clock_t start = clock();  // CPU的时钟计数，数据类型是long

	while (count < 5)
	{
		printf("请输入要猜的数字：");
		if (scanf("%d", &guess) != 1)
		{
			printf("输入无效，请重新输入\n");
			while (getchar() != '\n');   // getchar() --> <stdio.h>
			continue;
		}
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
			printf("恭喜你，猜对了\n");
			// 2. 结束时的"数"减开始的，得到中间的"数"（差值）
			// 3. 除以每秒多少下，就换算成"秒"
			printf("用时 %.0lf 秒\n", (double)(clock() - start) / CLOCKS_PER_SEC);
			break;
		}
		count++;
		printf("已用时 %.0lf 秒，还剩 %d 次机会\n", (double)(clock() - start) / CLOCKS_PER_SEC, 5 - count);
	}

	if (count == 5)
	{
		printf("5次都没有猜出来，游戏失败\n");
		printf("正确答案是：%d\n", r);
	}
}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));  // 随机数种子
	do
	{
		enmu();  // 游戏提示词
		printf("请输入：");
		scanf("%d", &input);  // 输入选项

		switch (input)
		{
		case 1:
			play_input();
			break;
		case 0:
			printf("游戏结束\n");
			break;
		default:
			printf("输入错误\n");
			break;
		}
	} while (input);
	return 0;
}