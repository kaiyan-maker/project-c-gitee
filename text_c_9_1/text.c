#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

/*  输⼊2个整数m和n，计算m和n的最⼤公约数，并打印出结果  */
int gcd(int a,int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main()
{
	// 方法一：
	int n = 0, m = 0;
	scanf_s("%d %d", &n, &m);

	int k = (m > n) ? n : m;

	while (1)
	{
		if (n % k == 0 && m % k == 0)
		{
			break;
		}
		k--;
	}

	printf("%d\n", k);

	// 方法二：(辗转相除法)
	int n = 0, m = 0, k = 0;
	scanf_s("%d %d", &n, &m);

	while (k = m % n)
	{
		m = n;
		n = k;
	}

	printf("%d\n", n);

	// 方法三：（辗转相除法递归）
	int n = 0, m = 0;
	scanf("%d %d", &n, &m);
	int p = gcd(n, m);

	printf("%d\n", p);
	return 0;
}

/*  输⼊2个整数m和n，计算m和n的最⼩公倍数，并打印出结果  */
int main()
{
	// 方法一：
	int n = 0, m = 0;
	scanf_s("%d %d", &n, &m);

	int k = (m > n ? m : n);

	while (1)
	{
		if (k % m == 0 && k % n == 0)
		{
			printf("%d\n", k);
			break;
		}
		k++;
	}

	// 方法二：（辗转相除法）
	int n = 0, m = 0;
	scanf_s("%d %d", &n, &m);

	int k = (m > n ? m : n);
	int mul = m * n;

	while (k = m % n)
	{
		m = n;
		n = k;
	}

	printf("%d", mul / n);
	return 0;
}

/*  计算 1/1 - 1/2 + 1/3 - 1/4 + 1/5 - … + 1/99 - 1/100 的值，并打印出结果  */
int main()
{
	double sum = 0;

	for (int i = 1;i <= 100;i++)
	{
		if (i % 2 == 1)
			sum += 1.0 / i;
		else
			sum -= 1.0 / i;
	}

	printf("%lf", sum);
	return 0;
}

/*  输⼊10个整数，写代码找出其中最⼤值和最⼩值，计算最⼤值和最⼩值的差，并打印出差值结果  */
int main()
{
	int arr[10] = { 0 };
	for (int i = 0;i < 10;i++)
	{
		scanf("%d", &arr[i]);
	}

	int Max = arr[0];
	int Min = arr[0];

	for (int j = 1;j < 10;j++)
	{
		if (arr[j] > Max)
			Max = arr[j];
		if (arr[j] < Min)
			Min = arr[j];
	}

	printf("%d",Max - Min);

	return 0;
}