#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10

/*  使用 C语言的库函数qsort函数 来实现选择排序 的算法  */
typedef struct
{
	int arr[MAX_SIZE];
	int sz;
}Array;

int int_cmp(const void* a,const void* b)
{
	return *(int*)a - *(int*)b;
}

void print_sel(const Array* ps)
{
	// 输出数据
	for (int i = 0;i < ps->sz;i++)
	{
		printf("%d ", *(ps->arr + i));
	}
}

/*  选择排序  */
int main()
{
	// 定义数组
	Array arr = { { 5,2,8,1,9,3,7,4,6,10 },10 };

	qsort(arr.arr, arr.sz, sizeof(int), int_cmp);
	print_sel(&arr);

	return 0;
}