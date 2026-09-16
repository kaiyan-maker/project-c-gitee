#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

void merge(int arr[], int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = 0;
	int size = right - left + 1;
	int* temp = (int*)malloc(size * sizeof(int));

	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			temp[k] = arr[i];
			k++;
			i++;
		} else {
			temp[k] = arr[j];
			k++;
			j++;
		}
	}

	while (i <= mid) {
		temp[k] = arr[i];
		k++;
		i++;
	}
	while (j <= right) {
		temp[k] = arr[j];
		k++;
		j++;
	}

	for (i = 0; i < size; i++) {
		arr[left + i] = temp[i];
	}

	free(temp);
}

void merge_sort(int arr[], int left, int right)
{
	int mid;

	if (left >= right) {
		return;
	}

	mid = (left + right) / 2;
	merge_sort(arr, left, mid);
	merge_sort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

int main()
{
	int n;
	int i;
	int* arr;

	printf("请输入元素个数: ");
	if (scanf("%d", &n) != 1 || n <= 0) {
		printf("输入无效\n");
		return 1;
	}

	arr = (int*)malloc(n * sizeof(int));
	if (arr == NULL) {
		printf("内存分配失败\n");
		return 1;
	}

	printf("请输入 %d 个数: ", n);
	for (i = 0; i < n; i++) {
		if (scanf("%d", &arr[i]) != 1) {
			printf("输入无效\n");
			free(arr);
			return 1;
		}
	}

	merge_sort(arr, 0, n - 1);

	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	free(arr);
	return 0;
}