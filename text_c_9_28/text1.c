#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

void Find(int arr[], int sz)
{
	int left = 0;
	int right = sz - 1;

	int k = 0;
	int mid = 0;
	printf("请输入需要寻找的数：");
	scanf("%d", &k);

	while (left <= right)
	{
		mid = (left + right) / 2;
		if (arr[mid] == k)
		{
			printf("已找到，下标：%d\n", mid);
			return mid;
		}
		else if (arr[mid] < k)
			left = mid + 1;
		else
			right = mid - 1;
	}

	printf("未找到\n");
}

int main()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	Find(arr, sz);
	return 0;
}