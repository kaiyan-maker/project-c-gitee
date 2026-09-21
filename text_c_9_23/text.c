#include<stdio.h>

/*   打印九九乘法表  */
int main()
{
	for (int i = 1;i < 10;i++)
	{
		for (int j = 1;j <= i;j++)
		{
			printf("%d*%d=%d ", j, i, j * i);
		}
		printf("\n");
	}
	return 0;
}