#include<stdio.h>

/*  使用普通数组 来实现 选择排序 的算算法  */
/*  选择排序  */
int main()
{
	// 定义数组
	int arr[10] = { 5,2,8,1,9,3,7,4,6,10 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	// 进行选择排序
	// 外层 循环 遍历数组中的 所有元素
	for (int i = 0;i < sz - 1;i++)
	{
		// 首先 把数组中的最小元素 设为最小值
		int MinIndex = i;
		// 内层循环 从第i个元素开始遍历，一直到末尾
		for (int j = i;j < sz;j++)
		{
			// 进行判断，如果元素 最小，则把这个元素 赋给 MinIndex
			if (arr[j] < arr[MinIndex])
			{
				MinIndex = j;
			}
		}

		// 定义一个临时变量，进行两个数的交换
		if (arr[MinIndex] != arr[i])
		{
			int temp = arr[i];
			arr[i] = arr[MinIndex];
			arr[MinIndex] = temp;
		}
	}

	// 输出数据
	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}