#include<stdio.h>

/*  使用 单纯的指针 的方法 来实现 选择排序 的算法  */
/*  选择排序  */
int main()
{
	// 定义数组
	int arr[10] = { 5,2,8,1,9,3,7,4,6,10 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	// 进行选择排序
	for (int* p = arr;p < arr + sz - 1;p++)
	{
		//int MinIndex = i;
		int* MInPtr = p;
		for (int* q = p;q < arr + sz;q++)
		{
			if (*q < *MInPtr)
			{
				MInPtr = q;
			}
		}

		if (*MInPtr != *p)
		{
			int temp = *p;
			*p = *MInPtr;
			*MInPtr = temp;
		}
	}

	// 输出数据
	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}