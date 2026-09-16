#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int partition(int arr[], int left, int right)
{
	int key = arr[right];
	int i = 0;
	for (i = left;i <= right - 1;i++)
	{
		if (arr[i] < key)
		{
			int temp = arr[left];
			arr[left] = arr[i];
			arr[i] = temp;
			left++;
		}
	}

	int tmp = arr[left];
	arr[left] = arr[right];
	arr[right] = tmp;

	return left;
}

void quicksort(int arr[], int left, int right)
{
	if (left >= right)
		return;
	else
	{
		int p = partition(arr, left, right);
		quicksort(arr, left, p - 1);
		quicksort(arr, p + 1, right);
	}
}

void print_sort(int arr[], int sz)
{
	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	int arr[10] = { 0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0;i < sz;i++)
	{
		scanf("%d", &arr[i]);
	}

	int left = 0;
	int right = sz - 1;

	quicksort(arr, left, right);

	print_sort(arr,sz);
	return 0;
}