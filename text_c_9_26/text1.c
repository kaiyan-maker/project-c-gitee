#include<stdio.h>

int partition(int arr[], int left, int right)
{
	int key = arr[right];
	for (int i = left;i <= right - 1;i++)
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

int main()
{
	int arr[10] = { 0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	int left = 0;
	int right = sz - 1;

	quicksort(arr, left, right);

	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}