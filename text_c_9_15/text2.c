#include<stdio.h>
#define MAX_SIZE 10

/*  使用 结构体＋指针＋函数封装 的方法 来实现 选择排序 的算法  */
typedef struct
{
	int arr[MAX_SIZE];
	int sz;
}Array;


void Sel(Array* ps)
{
	int sz = ps->sz;
	int* p = ps->arr;
	// 进行选择排序
	for (p = ps->arr;p < ps->arr + ps->sz - 1;p++)
	{
		//int MinIndex = i;
		int* MInPtr = p;
		for (int* q = p;q < ps->arr + ps->sz;q++)
		{
			if (*q < *MInPtr)
			{
				MInPtr = q;
			}
		}

		if (*MInPtr != *p)
		{
			int temp = *p;
			*p = *MInPtr;
			*MInPtr = temp;
		}
	}
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
	Array arr = {{ 5,2,8,1,9,3,7,4,6,10 },10};

	Sel(&arr);
	print_sel(&arr);
	
	return 0;
}