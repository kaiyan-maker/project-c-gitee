#include<stdio.h>

int main()
{
	int i, j;

	// 上半部分
	for (i = 1;i <= 7;i++)
	{
		for (j = 1;j <= 7 - i;j++)
		{
			printf(" ");
		}

		for (j = 1;j <= 2 * i - 1;j++)
		{
			printf("*");
		}
		printf("\n");
	}

	// 下半部分
	for (i = 6;i >= 1;i--)
	{
		for (j = 1;j <= 7 - i;j++)
		{
			printf(" ");
		}

		for (j = 1;j <= 2 * i - 1;j++)
		{
			printf("*");
		}
		printf("\n");
	}
	return 0;
}