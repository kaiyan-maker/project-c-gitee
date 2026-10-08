//#include<stdio.h>
//
//void Bottor_find(int arr[], int sz)
//{
//	int left = 0;
//	int right = sz - 1;
//
//	int mid = 0;
//	int k = 0;
//	scanf_s("%d", &k);
//
//	while (left <= right)
//	{
//		mid = (left + right) / 2;
//		if (arr[mid] == k)
//		{
//			printf("已找到，下标：%d\n", mid);
//			return mid;
//		}
//		else if (arr[mid] < k)
//			left = mid + 1;
//		else
//			right = mid - 1;
//	}
//
//	printf("未找到\n");
//}
//
//int main()
//{
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//
//	Bottor_find(arr, sz);
//	return 0;
//}