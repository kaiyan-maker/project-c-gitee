#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NDEBUG // 控制代码的开启或关闭
#include<assert.h>
/*  指针的最佳实践  */
// 永远初始化指针，未初始化的是野指针
// 使用前检查非空，使用if语句或者assert断言
// 别让边界问题毁了你的程序
// 数组退化为指针时，传递长度信息
// 永远不要返回栈空间的地址

//static double array_sum(const double* arr, int len)
//{
//	assert(arr != NULL);
//	assert(len > 0);
//	double total = 0.0;
//	for (int i = 0;i < len;i++)
//	{
//		total += arr[i];
//	}
//	return total;
//}
//
//double array_average(const double* arr, int len)
//{
//	if (!arr || len <= 0) return 0.0;
//
//	return array_sum(arr, len) / len;
//}
size_t my_strlen(const char* str)
{
	// 定义一个计数器
	size_t count = 0;
	while (*str != "\0")
	{
		count++;
		str++;
	}
	return count;
}

int main()
{
	//int* p;
	//*p = 10;

	//int ptr = (int*)malloc(4 * sizeof(int));
	//// ....
	//free(ptr);
	//ptr = NULL;
	//int m = 0;
	//m = 20;

	//const int n = 0;  // const 把变量变为常量
	//n = 20;

	// 通过指针取改常量的值
	//const int n = 0;
	//printf("n=%d\n", n);
	//int* p = &n;
	//*p = 20;
	//printf("n=%d\n", n);

	printf("%zu\n", my_strlen("abcdef"));
	return 0;
}