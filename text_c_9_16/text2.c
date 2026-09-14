#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10

/*  插入排序  */
 // 方法三：C语言的库函数 qsort 函数
typedef struct
{
	int arr[MAX_SIZE];
	int sz;
}Array;

void int_cmp(const void* a,const void* b)
{
	return *(int*)a - *(int*)b;
}

void print_sort(const Array* ps)
{
	for (int i = 0;i < ps->sz;i++)
	{
		printf("%d ", *(ps->arr + i));
	}
}

int main()
{
	Array arr = { { 98,199,299,43,54,65,32,12,23,2 },10 };

	qsort(arr.arr, arr.sz, sizeof(int), int_cmp);

	print_sort(&arr);

	return 0;
}