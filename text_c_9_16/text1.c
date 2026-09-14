#include<stdio.h>
#define MAX_SIZE 10

/*  插入排序  */
// 方法二：指针＋结构体＋函数
typedef struct
{
	int arr[MAX_SIZE];
	int sz;
}Array;

void Sort(Array* ps)
{
	int sz = ps->sz;
	int* p = ps->arr;
	for (int i = 1;i < ps->sz;i++)
	{
		for (int j = i;j > 0;j--)
		{
			if (p[j - 1] > p[j])
			{
				int temp = p[j - 1];
				p[j - 1] = p[j];
				p[j] = temp;
			}
		}
	}
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

	Sort(&arr);
	print_sort(&arr);

	return 0;
}