#include<stdio.h>
#define MAX_SIZE 10

// 定义一个结构体数组
typedef struct
{
	int arr[MAX_SIZE];
	int size;
}Array;

// 排序算法的核心思想
void Sort(Array* ps)
{
	int sz = ps->size;
	int* p = ps->arr;

	for (int i = 1;i < ps->size;i++)
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

// 打印整个数组的数据
void print_sort(const Array* ps)
{
	for (int i = 0;i < ps->size;i++)
	{
		printf("%d ", *(ps->arr + i));
	}
}

/*  插入排序  */
int main()
{
	// 定义一个数组
	Array arr = { { 10,9,7,8,6,4,5,2,3,1 } ,10 };

	Sort(&arr);

	print_sort(&arr);

	return 0;
}