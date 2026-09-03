#include<stdio.h>
#include<math.h>

/* 打印1~100000之间的所有自幂数（阿姆斯特朗数），用空格分隔
   自幂数：各位数字的n次方之和等于该数本身，如153 = 1^3 + 5^3 + 3^3 */
int main()
{
	for (int i = 1;i <= 100000;i++)
	{
		// 计算i的位数n
		int n = 0;
		int tmp = i;
		while (tmp % 10)  // 当最低位不为0时继续循环
		{
			n++;         // 位数加1
			tmp /= 10;  // 去掉最低位
		}

		// 计算i的每一位数字的n次方之和sum
		tmp = i;
		int sum = 0;
		while (tmp)
		{
			sum += (int)pow(tmp % 10, n); // 取最低位数字，计算其n次方并累加
			tmp /= 10;                     // 去掉最低位
		}

		// 如果各位数字的n次方之和等于该数本身，则为自幂数
		if (sum == i)
		{
			printf("%d ", i);
		}
	}
	return 0;
}

/* 输入一个整数n，打印2*n-1行的菱形图案
   例如输入7，输出13行的菱形，上半部分n行，下半部分n-1行 */
int main()
{
	int n = 0;
	scanf_s("%d", &n); // 读入菱形的半径（中心到顶点的行数）

	// 打印菱形上半部分（含中间最长行）
	for (int i = 0;i < n;i++)
	{
		// 打印前导空格：第i行有n-1-i个空格
		for (int j = 0;j < n - 1 - i;j++)
		{
			printf(" ");
		}

		// 打印星号：第i行有2*i+1个星号
		for (int j = 0;j < 2 * i + 1;j++)
		{
			printf("*");
		}
		printf("\n"); // 换行
	}

	// 打印菱形下半部分（不含中间最长行）
	for (int i = 0;i < n;i++)
	{
		// 打印前导空格：第i行有i+1个空格
		for (int j = 0;j <= i;j++)
		{
			printf(" ");
		}

		// 打印星号：第i行有2*(n-1-i)-1个星号
		for (int j = 0;j < 2 * (n - 1 - i) - 1;j++)
		{
			printf("*");
		}
		printf("\n"); // 换行
	}
	return 0;
}
