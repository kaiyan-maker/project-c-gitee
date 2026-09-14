#include<stdio.h>

/*  插入排序  */
 // 方法一：普通数组
int main()
{
	int arr[10] = { 98,199,299,43,54,65,32,12,23,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	for (int i = 1;i < sz;i++)
	{
		for (int j = i;j > 0;j--)
		{
			if (arr[j-1] > arr[j])
			{
				int temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
		}
	}

	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}