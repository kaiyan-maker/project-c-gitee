//#include<stdio.h>
//
//int partition(int arr[], int left, int right)
//{
//	// 5.选基准值
//	int key = arr[right];   // 选基准值
//	// 6.遍历整个数组
//	for (int i = left;i <= right;i++)
//	{
//		// 7.去拿基准值，跟遍历的值进行比较
//		if (arr[i] < key)
//		{
//			int temp = arr[left];
//			arr[left] = arr[i];
//			arr[i] = temp;
//			left++;
//		}
//	}
//
//	// 8.边界值进行归位
//	int tmp = arr[left];  // pivot 归位
//	arr[left] = arr[right];
//	arr[right] = tmp;
//	return left;
//}
//
//void qsortition(int arr[], int left, int right)
//{
//	// 4.比较边界值的大小
//	if (left >= right)
//		return;
//	else
//	{
//		int p = partition(arr, left, right);
//		// 9.调用函数，使数组进行快速排序
//		partition(arr, left, p - 1);
//		partition(arr, p + 1, right);
//	}
//}
//
//int main()
//{
//	// 1.定义数组，并求数组长度
//	int arr[10] = { 0 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//
//	// 2.输入数组内容
//	printf("请输入:");
//	for (int i = 0;i < sz;i++)
//	{
//		scanf_s("%d", &arr[i]);
//	}
//
//	// 3.定义边界值
//	int left = 0;   // 左边
//	int right = sz - 1;  // 右边
//
//	qsortition(arr, left, right);
//
//	// 10.打印输出数组内容
//	for (int i = 0;i < sz;i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}