#include<stdio.h>
#define MAX_SIZE 10

typedef struct
{
	int arr[MAX_SIZE];
	int size;
}Array;

void Sort(Array* ps)
{
	int sz = ps->size;
	int* p = ps->arr;
	// 外层循环依次遍历数据
	for (p = ps->arr;p < ps->arr + ps->size - 1;p++)
	{
		//int MinIndex = i;  // 把数组的最小值赋值给MinIdex
		int* MinStr = p;
		// 内层循环 从i开始遍历，一直遍历到数组的结尾
		for (int* q = p;q < ps->arr + ps->size;q++)
		{
			// 如果遍历出来的数据小于数组的最小值，就进行两数的交换
			if (*q < *MinStr)
			{
				MinStr = q;
			}
		}

		// 判断两数是否相等，若相等，就进行两数的交换
		if (*p != *MinStr)
		{
			int temp = *p;
			*p = *MinStr;
			*MinStr = temp;
		}
	}
}

// 依次循环遍历整个数组
void print_sort(const Array* ps)
{
	for (int i = 0;i < ps->size;i++)
	{
		printf("%d ", *(ps->arr + i));
	}
}

/*  选择排序  */
int main()
{
	//定义一个结构体数组，并求数组的大小
	Array arr = { { 5,2,8,1,9,3,7,4,6,10 },10 };

	Sort(&arr);

	print_sort(&arr);

	return 0;
}