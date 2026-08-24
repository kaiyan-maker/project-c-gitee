#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

/*  底层程序设计  */

int chenk_sed()
{
	int i = 1;
	scanf("%d", &i);
	//if (*((char*) & i) == 1)
	//	return 1;
	//else
	//	return 0;

	return (*((char*)&i));
}

int main()
{
	/*  小端字节序：低位字节序保存在低地址处，高位字节序保存在高地址处  
		大端字节序：低位字节序保存在高地址处，高位字节序保存在低地址处*/
	//int a = 0x11223344;

	// 请简述⼤端字节序和⼩端字节序的概念，设计⼀个⼩程序来判断当前机器的字节序。（10分）
	//int ret = chenk_sed();

	//if (ret == 1)
	//	printf("小端\n");
	//else
	//	printf("大端\n");

	//int num = 10;
	//int n = num << 1;
	//printf("num = %d\n", num);
	//printf("n = %d\n", n);

	//int a = 8;
	//unsigned int ux = (unsigned int)a;
	////ux = ux >> 1;
	//ux >>= 1;

	// 不能创建临时变量（第三个变量），实现两个整数的交换。
	int n1 = 10;
	int n2 = 20;
	//int c = 0;
	//printf("交换前：n1=%d,n2=%d\n", n1, n2);
	//c = n1;
	//n1 = n2;
	//n2 = c;
	//printf("交换后：n1=%d,n2=%d\n", n1, n2);

	//printf("交换前：n1=%d,n2=%d\n", n1, n2);
	//n1 = n1 ^ n2;
	//n2 = n1 ^ n2;
	//n1 = n1 ^ n2;
	//printf("交换后：n1=%d,n2=%d\n", n1, n2);

	// 求⼀个整数存储在内存中的⼆进制中1的个数
	//int num = -1;
	//scanf("%d", &num);

	//int count = 0;  // 计数器
	//while (num)
	//{
	//	count++;
	//	num = num & (num - 1);
	//}
	//printf("二进制中的 %d 个1\n", count);

	/*  ⼆进制位置0或者置1操作符
编写代码将13的⼆进制序列的第5位修改为1，然后再改回0  */
	//int a = 19;

	//a = a | (1 << 4);
	//printf("a=%d\n", a);

	//a = a & ~(1 << 4);
	//printf("a=%d\n", a);
	return 0;
}