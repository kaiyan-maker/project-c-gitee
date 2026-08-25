#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//void bubble_sort(int* arr,int sz)
//{
//	for (int i = 0;i < sz;i++)
//	{
//		int flag = 1;  // 假如有序
//		for (int j = 0;j < sz-i-1;j++)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				flag = 0;  // 发生交换就说明，无序
//				int tmp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = tmp;
//			}
//		}
//
//		if (flag == 1) // 没交换就说明有序，无需交换
//			break;
//	}
//}

/*  指针和数组  */
//int main()
//{
//	//int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//
//	////printf("&arr[0]:%p\n", &arr[0]);
//	////printf("arr:    %p\n", arr);
//	////printf("&arr:   %p\n", &arr);
//	////int* p = &arr[0];
//	//int* p = arr;
//	//int sz = sizeof(arr) / sizeof(arr[0]);
//
//	//for (int i = 0;i < sz;i++)
//	//{
//	//	printf("*（%d+%d） = %d\n",*p,i,*(p + i));
//	//}
//
//	//const char* pstr = "hello bit!";  // pstr指针变量  -->  字符串“hello bit!”
//	//printf("%s\n", *pstr);
//	
//	//char str1[] = "hello bit!";
//	//char str2[] = "hello bit!";
//	//const char* str3 = "hello bit!";
//	//const char* str4 = "hello bit!";
//
//	//if (str1 == str2)
//	//	printf("str1 and str2 are some\n");
//	//else
//	//	printf("str1 and str2 are not some\n");
//
//	//if (*str3 == *str4)
//	//	printf("str3 and str4 are some\n");
//	//else
//	//	printf("str3 and str4 are not some\n");
//	
//	//int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	//int sz = sizeof(arr) / sizeof(arr[0]);
//
//	////Print(arr, sz);
//	//Print(arr, sz);
//	
//	// 冒泡排序
//	int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//
//	bubble_sort(arr, sz);
//
//	for (int i = 0;i < sz;i++)
//	{
//		printf("%d ", arr[i]);
//	}
//
//	return 0;
//}

/* 数组指针变量  */
// 数组指针变量是 一个指针变量
//整型指针变量：int* pint
// 浮点型指针变量：float* pf;
// 数组指针变量 存放的是 数组的地址，指向数组的指针变量
// 语法：int (*p)[10];

//void test(int (*p)[5], int r,int c)
//{
//	for (int i = 0;i < r; i++)
//	{
//		for (int j = 0;j < c;j++)
//		{
//			printf("%d ", *((*p+i) + j));
//		}
//		printf("\n");
//	}
//}

//int main()
//{
//	//int arr[10] = { 0 };
//	////&arr;
//	//int(*p)[10] = &arr;  // 数组指针变量
//
//	// 二维数组传参
//	// 类型是： int (*)[];
//	int arr[3][5] = { {1,2,3,4,5},{2,3,4,5,6},{3,4,5,6,7} };
//	test(arr, 3, 5);
//	return 0;
//}


/* 指针数组 */
// 指针数组：存放的是指针，指向一个数组（每一个元素用来存放的是一个地址的）
//int main()
//{
//	//指针数组模拟二维数组
//	int arr1[] = { 1,2,3,4,5 };
//	int arr2[] = { 2,3,4,5,6 };
//	int arr3[] = { 3,4,5,6,7 };
//
//	int* ptr[3] = {arr1,arr2,arr3};
//
//	for (int i = 0;i < 3;i++)
//	{
//		for (int j = 0;j < 5;j++)
//		{
//			printf("%d ", ptr[i][j]);
//		}
//		printf("\n");
//	}
//	return 0;
//}

//int main()
//{
//	char* c[] = { "ENTER","NEW","POINT","FIRST" };
//	char** cp[] = { c + 3,c + 2,c + 1,c };
//	char*** cpp = cp;
//	printf("%s\n", **++cpp);
//	printf("%s\n", *-- * ++cpp + 3);
//	printf("%s\n", *cpp[-2] + 3);
//	printf("%s\n", cpp[-1][-1] + 1);
//	return 0;
//}


/*   指针和动态内存管理  */
#include<stdlib.h>
int main()
{
	// 向内存的堆区申请⼀块连续可⽤的空间，并返回指向这块空间的起始地址。
	//语法：void* malloc(size_t size);
	// 释放之前通过动态内存分配函数
	// 语法：void free(void* ptr);
	// 函数的功能是为 num 个⼤⼩为 size 的元素开辟⼀块空间，并且把空间的每个字节初始化为 0。
	// 语法：void* calloc(size_t num, size_t size);
	// 重新调整之前分配的内存块的⼤⼩，它可以在不丢失原有数据的情况下，扩⼤或缩⼩动态分配的内存块。
	// 语法：void* realloc(void* ptr, size_t size);

	//int num = 0;
	//scanf("%d", &num);
	//// 创建动态内存
	//int* ptr = (int*)malloc(num * sizeof(int));
	////int* ptr = calloc(10, sizeof(int));
	//if (ptr != NULL)
	//{
	//	//for (int i = 0;i < num;i++)
	//	//{
	//	//	*(ptr + i) = 0;
	//	//}
	//	for (int i = 0;i < num;i++)
	//	{
	//		printf("%d ", *(ptr + i));
	//	}
	//}
	//else {
	//	printf("malloc失败\n");
	//	return 1;
	//}

	//// 释放内存
	//free(ptr);
	//ptr = NULL; // 如果ptr不置为NULL,ptr就会变为悬空指针
	// 悬空指针：指针曾经有效，但它指向的内存已经被释放或失效了，
	// 指针⾥还保留着原来的地址

	//int* ptr = malloc(20);

	//if (ptr != NULL)
	//{
	//	int * tmp = realloc(ptr, 40);
	//}

	int* ptr = malloc(100);
	if (ptr != NULL)
	{
		perror(ptr);
	}
	else {
		return 1;
	}
	// 代码1
	ptr = realloc(ptr, 1000);

	// 代码2
	int* p = realloc(ptr, 1000);

	if (p != NULL)
	{
		ptr = p;
		p = NULL;
	}

	free(ptr);
	ptr = NULL;

	return 0;
}


/*  动态内存管理的常见错误  */
// 1.对NULL指针的解引用操作
// 2.对动态开辟空间的越界访问
// 3.对非动态开辟内存使用free释放
// 4.使用free释放一块动态开辟内存的一部分
// 5.对同一块动态内存多次释放
// 6.动态开辟内存忘记释放（内存泄露）

struct st_type
{
	int i;
	int a[0]; // 柔性数组成员
};

int main()
{
	printf("%d\n", sizeof(struct st_type));
	return 0;
}

// 柔性数组的特点
// 1.结构中的柔性数组成员前⾯必须⾄少⼀个其他成员。
// 2.sizeof 返回的这种结构⼤⼩不包括柔性数组的内存。
// 3.包含柔性数组成员的结构⽤ malloc() 函数进⾏内存的动态分配，并且分配的内存应该⼤于结构
//	的⼤⼩，以适应柔性数组的预期⼤⼩。