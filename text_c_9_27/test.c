#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

/*  归并排序的第二次练习  */
void marage(int arr[], int left, int mid, int right)
{
	int i = left;
	int j = right;
	int k = 0;
	int size = right - left + 1;
	int* temp = (int*)malloc(size * sizeof(int));

	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j])
		{
			temp[k] = arr[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = arr[j];
			k++;
			j++;
		}
	}

	while (i <= mid)
	{
		temp[k] = arr[i];
		k++;
		i++;
	}

	while (j <= right)
	{
		temp[k] = arr[j];
		k++;
		j++;
	}

	for (int i = 0;i < size;i++)
	{
		arr[left + i] = temp[i];
	}

	free(temp);
}

void marage_sort(int arr[], int left, int right)
{
	int mid;   // 取中间的数，取中位数
	if (left >= right)  // 只有当左边的  >= 右边的，直接返回
		return;
	mid = (left + right) / 2;     
	marage_sort(arr, left, mid);
	marage_sort(arr, mid + 1, right);
	marage(arr, left, mid, right);
}

int main()
{
	int n;  // 输入元素的个数
	int* arr;  // 指针数组

	printf("请输入元素个数：");   // 对输入的元素个数进行判断，输入的元素个数不能为 1 或 负数
	if (scanf("%d", &n) != 1 || n <= 0)
	{
		printf("输入无效！\n");
		return 1;
	}

	int* p = (int*)malloc(n * sizeof(int));   // 开辟一块 动态内存空间
	if (p == NULL)
	{
		printf("动态申请的内存失败！\n");
		return 1;
	}

	printf("输入 %d 个数：",n);   // 数组里的元素不能为1，否则释放内存
	for (int i = 0;i < n;i++)
	{
		if (scanf("%d", &arr[i]) != 1)
		{
			printf("输入无效！\n");
			free(arr);
			return 1;
		}
	}

	marage_sort(arr, 0, n - 1);  // 调用排序函数

	for (int i = 0;i < n;i++)  // 打印数组元素
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	free(arr);  // 既然开辟内存，那就必须有释放内存，如果不释放内存，会导致悬空指针，变成一个野指针

	return 0;
}