#include<stdio.h>
#include<stdlib.h>

int main()
{
	/* 练习使用动态内存相关的4个函数，并调试观察。
	malloc、calloc、realloc、free */

	/*  malloc  */
	int* ps = (int*)malloc(5 * sizeof(int));
	if (ps == NULL) {
		printf("malloc失败\n");
		return 1;
	}

	int i = 0;
	for (i = 0;i < 5;i++) {
		ps[i] = i + 1;
	}

	for (i = 0;i < 5;i++) {
		printf("%d ", ps[i]);
	}
	printf("\n");

	free(ps);
	ps = NULL;

	/*  calloc  */
	int* ps = (int*)calloc(5, sizeof(int));
	if (ps == NULL) {
		printf("malloc失败\n");
		return 1;
	}

	int i = 0;
	for (i = 0;i < 5;i++) {
		ps[i] = i + 1;
	}

	for (i = 0;i < 5;i++) {
		printf("%d ", ps[i]);
	}
	printf("\n");

	free(ps);
	ps = NULL;

	/*  realloc  */
	int* ps = (int*)malloc(5 * sizeof(int));
	if (ps == NULL) {
		printf("malloc失败\n");
		return 1;
	}

	int i = 0;
	for (i = 0;i < 5;i++) {
		ps[i] = i + 1;
	}

	for (i = 0;i < 5;i++) {
		printf("%d ", ps[i]);
	}
	printf("\n");

	int* tem = (int*)realloc(ps, 10 * sizeof(int));
	if (tem == NULL) {
		printf("realloc失败\n");
		return 1;
	}
	else {
		ps = tem;
		for (int i = 0;i < 10;i++) {
			printf("%d", ps[i]);
		}
	}

	free(ps);
	ps = NULL;
	return 0;
}