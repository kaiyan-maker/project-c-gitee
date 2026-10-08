//#include<stdio.h>
//#define MAX_SIZE 10   // 定义一个全局变量
//
//// 定义一个结构体，用于表示数组的结构，用 typedef 进行结构体声明 
//typedef struct
//{
//	int arr[MAX_SIZE];
//	int sz;
//}Array;
//
//void Sort(Array* ps)
//{
//	int sz = ps->sz;
//	int* p = ps->arr;
//	for (p = ps->arr;p < ps->arr + ps->sz - 1;p++)
//	{
//		// 定义一个临时变量，用于存储指针p的地址
//		int* MinStr = p;
//		// 从第p个位置开始遍历到数组的结尾，依次递增
//		for (int* q = p;q < ps->arr + ps->sz;q++)
//		{
//			if (*q < *MinStr)
//			{
//				MinStr = q;
//			}
//		}
//
//		// 判断两数是否相等，如果相等，就交换两数的位置，并且定义一个临时变量
//		if (*p != *MinStr)
//		{
//			int temp = *p;
//			*p = *MinStr;
//			*MinStr = temp;
//		}
//	}
//}
//
//// 使用指针打印数组的内容
//void print_sort(const Array* ps)
//{
//	for (int i = 0;i < ps->sz;i++)
//	{
//		printf("%d", *(ps->arr + i));
//	}
//}
//
//int main()
//{
//	Array arr = { {10,9,8,7,6,5,4,3,2,1},10 };
//
//	Sort(&arr);
//
//	print_sort(&arr);
//
//	return 0;
//}