#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#define MAX_SIZE 10

typedef struct
{
	int arr[MAX_SIZE];
	int size;
}Array;

int partition(int arr[], int left, int right)
{
	int key = arr[right];  // 选基准
	for (int i = left;i <= right - 1;i++)  // 遍历扫描
	{
		if (arr[i] < key)
		{
			int temp = arr[left];  // 交换，把小数移到左区
			arr[left] = arr[i];
			arr[i] = temp;
			left++;    // 小于区，边界右移
		}
	}

	int tmp = arr[left];  // pivot 归位
	arr[left] = arr[right];
	arr[right] = tmp;
	return left;  // 返回key 的下标
}

void quicksort(int arr[],int left,int right)
{
	if (left >= right)
		return;
	else
	{
		int p = partition(arr, left, right);  // 拿基准位置
		quicksort(arr, left, p - 1);   // 排左边
		quicksort(arr, p + 1, right);  // 排右边
	}
}
int main()
{
	// 定义数组
	int arr[10] = {0};
	int sz = sizeof(arr) / sizeof(arr[0]);

	printf("请输入：");
	for (int i = 0;i < sz;i++)
	{
		scanf("%d", &arr[i]);
	}

	int left = 0;  // 左边界
	int right = sz - 1;  // 右边界

	quicksort(arr, left, right);

	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}