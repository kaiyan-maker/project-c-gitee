#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 10

/*  冒泡排序  */
typedef struct
{
	int arr[MAX_SIZE];
	int size;
}Array;

void Sort(int arr[], int sz)
{
	// 2.外层循环遍历整个数组，内层循环遍历还未排序的数组
	for (int i = 0;i < sz - 1;i++)
	{
		for (int j = 0;j < sz - i - 1;j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void print(int arr[], int sz)
{
	// 3.循环遍历排序好后的整个数组
	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	// 1.定义一个数组，并算出数组的个数
	int arr[10] = { 0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0;i < sz;i++)
	{
		scanf("%d", &arr[i]);
	}
	
	// 调用处理冒泡排序的函数
	Sort(arr,sz);
	
	// 调用打印功能的函数
	print(arr,sz);

	return 0;
}