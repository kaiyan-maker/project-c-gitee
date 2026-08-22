#include<stdio.h>

 /*   指针的核心知识   */

//size_t my_strlen(char* str)
//{
//	size_t count = 0;
//	while (*str != '\0')
//	{
//		count++;
//		str++;
//	}
//	return count;
//}


size_t my_strlen(char* str)
{
	char* end = str;
	while (*end != '\0')
		end++;
	return end - str;
}

void Ps(int* n1,int* n2)
{
	int tmp = 0;
	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}
int main()
{
	//int a = 10;
	//int* p = &a;  // 这是一种指针变量，把a的地址存到指针p中
	//int* p = NULL; // 不使用赋值为空指针
	//printf("%d\n", &p);
	
	//int a = 0;
	//int* p = &a;

	//*p = 0;   // 对a 进行解引用
	//printf("%d\n", *p);
	
	//printf("%zd\n", sizeof(char*));
	//printf("%zd\n", sizeof(short*));
	//printf("%zd\n", sizeof(int*));
	//printf("%zd\n", sizeof(double*));
	
	//int n = 0x11223344;
	//char* p = (char*)&n;
	//*p = "a";

	//int n = 10;
	//int* p = &n;
	//char* ps = (char*)&n;

	//printf("%p\n", &n);
	//printf("%p\n", p);
	//printf("%p\n", p+1);
	//printf("%p\n", ps);
	//printf("%p\n", ps+1);

	//int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	//int*p = &arr[0];
	//int sz = sizeof(arr) / sizeof(arr[0]);

	//int i = 0;
	//for (i = 0;i < sz;i++)
	//{
	//	printf("%d ", *(p + i));
	//}


	//printf("%zu\n", my_strlen("abcdef"));


	//int num1 = 10;
	//int num2 = 20;
	//printf("交换前：%d %d\n", num1,num2);
	//Ps(&num1, &num2);
	//printf("交换后：%d %d\n", num1,num2);

	/*  传址调⽤，可以让函数和主调函数之间建⽴真正的联系，在函数内部可以修改主调函数中的
	变量；所以未来函数中只是需要主调函数中的变量值来实现计算，就可以采⽤传值调⽤。
	如果函数内部要修改主调函数中的变量的值，就需要传址调⽤。 */

	int a = 10;
	int* p = &a;

	int** p1 = &p;

	// 二级指针存放的是 一级指针的地址；
	return 0;
}