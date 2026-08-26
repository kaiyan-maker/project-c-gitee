#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

/*   指针和函数   */
//int text()
//{
//	printf("haha\n");
//}
//
//int Add(int x, int y)
//{
//	return x + y;
//}
//
//int main()
//{
//
//	//printf("%p\n", text);
//	//printf("%p\n", &text);
//	
//	//int (*ptf)(int, int) = Add;
//	//int (*ptf1)(int x, int y) = &Add;
//
//	// typedef 关键字
//	//typedef unsigned int uint;  // 将unsigned int 重命名为 uint
//	//typedef int* ptr_t;  // 将int* 重命名为 ptr_t
//
//	//typedef int(*parr_t)[5];  // parr_t 为新定义的名字
//	//typedef int(*parr_tt)(int);  // parr_t 为新定义的名字
//
//	//typedef void (*def_er)(int);
//	//def_er signal(int, def_er);
//	//int* arr[10];
//
//	//int (*parr1[3])();
//	//int* parr2[3]();
//	//int(*)() parr1[5];
//
//	return 0;
//}


/*  函数指针变量  */
// -->  存放函数地址，指向函数的指针变量

/*  函数指针数组  */
// --> 存放函数的地址 的数组

void menu()
{
	printf("-----------------------------\n");
	printf("--- 1.add       2.sub     ---\n");
	printf("--- 3.mul       4.div     ---\n");
	printf("---       0.exit          ---\n");
	printf("-----------------------------\n");
}

int Add(int x,int y)
{
	return x + y;
}

int Sub(int x,int y)
{
	return x - y;
}

int Mul(int x, int y)
{
	return x * y;
}

int Div(int x, int y)
{
	return x / y;
}

//int main()
//{
//	int input = 0;
//	int a = 0;
//	int b = 0;
//
//	do
//	{
//		menu();
//		printf("请选择：");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//			printf("请输入两个数：");
//			scanf("%d %d", &a, &b);
//			int r1 = Add(a, b);
//			printf("r1 = %d\n", r1);
//			break;
//		case 2:
//			printf("请输入两个数：");
//			scanf("%d %d", &a, &b);
//			int r2 = Sub(a, b);
//			printf("r2 = %d\n", r2);
//			break;
//		case 3:
//			printf("请输入两个数：");
//			scanf("%d %d", &a, &b);
//			int r3 = Mul(a, b);
//			printf("r3 = %d\n", r3);
//			break;
//		case 4:
//			printf("请输入两个数：");
//			scanf("%d %d", &a, &b);
//			int r4 = Div(a, b);
//			printf("r4 = %d\n", r4);
//			break;
//		case 0:
//			printf("拜拜\n");
//			break;
//		default:
//			printf("输入错误\n");
//			break;
//		}
//	} while (input);
//	return 0;
//}


//int main()
//{
//	int input = 0;
//	int a = 0;
//	int b = 0;
//	int r1 = 0;
//
//	int (*ps[5])(int x, int y) = { 0,Add,Sub,Mul,Div };  // 函数指针数组
//
//	do
//	{
//		menu();
//		printf("请选择：");
//		scanf("%d", &input);
//
//		if (input <= 4 && input >= 1)
//		{
//			printf("请输入两个数：");
//			scanf("%d %d", &a, &b);
//			r1 = (*ps[input])(a, b);
//			printf("r1 = %d\n", r1);
//		}
//		else if (input == 0)
//		{
//			printf("拜拜\n");
//		}
//		else {
//			printf("输入错误\n");
//		}
//	} while (input);
//	return 0;
//}


// 回调函数  -->  通过函数指针调用的函数

//void calc(int (*ps)(int, int))
//{
//	int a = 0;
//	int b = 0;
//	printf("请输入两个数：");
//	scanf("%d %d", &a, &b);
//	int r1 = ps(a, b);
//	printf("r1 = %d\n", r1);
//}
//
//int main()
//{
//	int input = 0;
//	int a = 0;
//	int b = 0;
//
//	do
//	{
//		menu();
//		printf("请选择：");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//			calc(Add);
//			break;
//		case 2:
//			calc(Sub);
//			break;
//		case 3:
//			calc(Mul);
//			break;
//		case 4:
//			calc(Div);
//			break;
//		case 0:
//			printf("拜拜\n");
//			break;
//		default:
//			printf("输入错误\n");
//			break;
//		}
//	} while (input);
//	return 0;
//}


/*   qsort    */
// qsort 可以排序任意类型的数据
/*
	语法：void qsort(void* base,size_t num,size_t size,int (*cmp)(const void*,const void*));
	base 是指向待排序数据的起始位置
	num 是待排序数据的元素个数
	size 是待排序数据中⼀个元素的宽度
	cmp - 是函数指针，指针指向的函数，在排序时，⽤来⽐较2个数据的⼤⼩关系的⽐较函数
*/
//void bubble_sort(int arr[], int sz)
//{
//	for (int i = 0;i < sz;i++)
//	{
//		for (int j = 0;j < sz - i - 1;j++)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				int tmp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = tmp;
//			}
//		}
//	}
//}
//
//int main()
//{
//	int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//
//	bubble_sort(arr, sz);
//	return 0;
//}
#include<stdlib.h>

//int temp(const void* p1,const void* p2)
//{
//	return *(int*)p1 - *(int*)p2;
//}
//int main()
//{
//	int arr[] = { 3,2,1,4,5,6,9,10,8 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//
//	qsort(arr, sz, sizeof(int), temp);
//	for (int i = 0;i < sz;i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}

//struct Stu
//{
//	char name[20];
//	int age;
//};
//
//int cmp_name(const void* p1,const void* p2)
//{
//	return strcmp(((struct Stu*)p1)->name, ((struct Stu* )p2)->name);
//}
//void test2()
//{
//	struct Stu s1[] = {{"zhangsan",20},{"lisi",21},{"wangwu",22}};
//	int sz = sizeof(s1) / sizeof(s1[0]);
//	qsort(s1, sz, sizeof(s1[0]), cmp_name);
//}
//
//int main()
//{
//	test2();
//	return 0;
//}

#include<string.h>

// 实现 bubble_sort，模拟 qsort 的通⽤排序函数
// 参数说明：
//   base - 指向待排序数组的起始地址（void* 可接收任意类型）
//   num  - 数组中元素的个数
//   size - 每个元素的字节宽度
//   cmp  - 比较函数指针，⽤于⽐较两个元素的⼤⼩
//          返回 > 0 表示前⼀个元素更⼤，需要交换
void bubble_sort(void* base, size_t num, size_t size, int (*cmp)(const void*, const void*))
{
	// 外层循环：总共需要 num-1 轮冒泡
	for (size_t i = 0; i < num - 1; i++)
	{
		// 内层循环：每轮将最⼤元素冒泡到末尾，已排好的末尾元素不再⽐较
		for (size_t j = 0; j < num - i - 1; j++)
		{
			// 通过 (char*)base 进⾏字节级别的指针运算，定位到第 j 和 j+1 个元素
			// 调⽤回调函数⽐较⼤⼩，若前 > 后则交换
			if (cmp((char*)base + j * size, (char*)base + (j + 1) * size) > 0)
			{
				// 交换两个元素：借助 memcpy 按字节拷贝，不依赖具体类型
				char tmp[size];                                  // 临时缓冲区（变长数组）
				memcpy(tmp, (char*)base + j * size, size);       // tmp = arr[j]
				memcpy((char*)base + j * size, (char*)base + (j + 1) * size, size);  // arr[j] = arr[j+1]
				memcpy((char*)base + (j + 1) * size, tmp, size); // arr[j+1] = tmp
			}
		}
	}
}

// ⽐较函数：⽤于排序 int 类型数组（升序）
int cmp_int(const void* p1, const void* p2)
{
	return *(int*)p1 - *(int*)p2;  // 若 p1 指向的值更⼤，返回正数，触发交换
}

int main()
{
	int arr[] = { 10,9,8,7,6,5,4,3,2,1 };
	int sz = sizeof(arr) / sizeof(arr[0]);  // 计算数组元素个数

	// 调⽤通⽤冒泡排序：传⼊数组地址、元素个数、元素⼤⼩、⽐较函数
	bubble_sort(arr, sz, sizeof(int), cmp_int);

	// 打印排序结果
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}