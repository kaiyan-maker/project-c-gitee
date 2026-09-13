/*  冒泡排序  */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define MAX_SIZE 10

// 方法一：
int Sort(int arr[],int sz)
{
	int* ps = arr[sz-1];
	int count = 0;
	 // 循环遍历数组的所有数据
	for (int i = 0;i < sz - 1;i++)
	{
		 // 循环遍历完数据之后，对剩下的数组数据进行排序
		for (int j = 0;j < sz - i - 1;j++)
		{
			count++;
			 // 比较两个数的大小，并进行交换
			if (arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void print_sort(int arr[], int sz)
{
	// 输出数据
	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}
}


// 方法二：（指针）
void print_sort(int arr[],int sz)
{
	int* p = arr;
	 // 输出数据
	for (int i = 0;i < sz;i++)
	{
		printf("%d ", *(p + i));
	}
}

int main()
{
	//int n = 0;
	//scanf_s("%d", &n);
	// 定义一个变长数组
	//int arr[n];  // C99里支持变长数组，VS里不支持变长数组的
	int arr[10] = { 0 };

	// 输入乱序的数据
	printf("请输入：");
	//scanf_s("%d", &arr[0]);

	// 数组的大小
	int sz = sizeof(arr) / sizeof(arr[0]);

	// 手动输入
	for (int* p = arr;p < arr + sz;p++)
	{
		scanf_s("%d", p);
	}

	// 进行函数的调用，并依次实现函数封装的功能
	int ret = Sort(arr, sz);  
	print_sort(arr, sz);

	return 0;
}


/*  方法三：(结构体＋指针)  */

// 结构体封装：数组本身+有效元素个数
typedef struct
{
	int data[MAX_SIZE];
	int size;
}Array;

// 排序：接受结构体指针，内部用指针遍历
void Sort(Array* pa)
{
	int sz = pa->size;
	int* p = pa->data;

	for (int i = 0;i < sz - 1;i++)
	{
		for (int j = 0; j < sz - i - 1;j++)
		{
			// 相邻元素左指针
			int* pa1 = p + j;
			// 相邻元素右指针
			int* pa2 = p + j + 1;
			if (*pa1 > *pa2)
			{
				int temp = *pa1;
				*pa1 = *pa2;
				*pa2 = temp;
			}
		}
	}
}

void print_sort(const Array*pa)
{
	int* p = pa->data;
	for (int i = 0;i < pa->size;i++)
	{
		printf("%d ", *(p + i));
	}
	printf("\n");
}
int main()
{
	// 用结构体统一定义数据和长度
	Array arr = { {10,9,8,7,6,5,4,3,2,1},10 };

	Sort(&arr);
	print_sort(&arr);
	return 0;
}

/*  方法四：（qsort方法）  */
int int_cmp(const void* a,const void* b)
{
	return *(int*)a - *(int*)b;
}

int main()
{
	// 用结构体统一定义数据和长度
	Array arr = { {10,9,8,7,6,5,4,3,2,1},10 };

	qsort(arr.data, arr.size, sizeof(int), int_cmp);
	print_sort(&arr);
	return 0;
}