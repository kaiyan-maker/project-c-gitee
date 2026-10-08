//#include<stdio.h>
//#define MAX_SIZE 10
//
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
//
//	for (int i = 0;i < ps->sz;i++)
//	{
//		for (int j = i;j > 0;j--)
//		{
//			if (p[j - 1] > p[j])
//			{
//				int temp = p[j - 1];
//				p[j - 1] = p[j];
//				p[j] = temp;
//			}
//		}
//	}
//}
//
//void print_sort(const Array* ps)
//{
//	for (int i = 0;i < ps->sz;i++)
//	{
//		printf("%d ", *(ps->arr + i));
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