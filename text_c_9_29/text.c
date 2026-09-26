#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

/*  求n 的阶乘  */
int Frb(int n)
{
	if (n == 0)
		return 1;
	else
		return n * Frb(n - 1);
}

int main()
{
	int n = 0;
	scanf("%d", &n);

	int p = Frb(n);

	printf("%d\n", p);
	return 0;
}