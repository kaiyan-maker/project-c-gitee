#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

/*  求第n个裴波纳契数列  */
int Frb(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return Frb(n - 1) + Frb(n - 2);
}

int main()
{
	int n = 0;
	scanf("%d", &n);

	int p = Frb(n);

	printf("%d\n", p);
	return 0;
}