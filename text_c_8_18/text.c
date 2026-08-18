#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//int main()
//{
//	// 输⼊⼀个正的整数，逆序打印这个整数的每⼀位
//	int num = 0;
//	scanf("%d", &num);
//
//	while (num > 1)
//	{
//		printf("%d", num % 10);
//		num = num / 10;
//	};
//
//	printf("%d", num);
//	return 0;
//}

//int main()
//{
//	// 输⼊⼀个正整数，打印所有⼩于或者等于这个数的，正偶数
//	int n = 0;
//	scanf("%d", &n);
//
//	int i = 0;
//	while (i <= n)
//	{
//		printf("%d ", i);
//		i += 2;
//	}
//	printf("\n");
//	return 0;
//}

//int main()
//{
//	// 在屏幕上打印1~10的值
//	for (int i = 1;i <= 10;i++) {
//		printf("%d ", i);
//	}
//	return 0;
//}

//int main()
//{
//	int sum = 0;
//	// 计算1~100之间3的倍数的数字之和
//	for (int i = 1;i <= 100;i++)
//	{
//		if (i % 3 == 0)
//		{
//			sum += i;
//		}
//	}
//	printf("%d", sum);
//	return 0;
//}

//int main()
//{
//	/* 计算机银⾏存款结余
//银⾏利息是3%，本⾦10000元
//计算出5年中，每⼀年年底，本⾦ + 利息的结余 */
//
//	double money = 10000;  // 本金
//
//	int year = 0;
//
//	for (year = 1;year <= 5;year++)
//	{
//		money *= 1.03;
//		printf("第 %d 年： %.2f 元\n", year, money);
//	}
//
//	return 0;
//}

//int main()
//{
//	// 在屏幕上打印1~10的值
//	int i = 1;
//
//	//for (i = 1;i <= 10;i++)
//	//{
//	//	printf("%d ", i);
//	//}
//	printf("\n");
//	do 
//	{
//		printf("%d ", i);
//		i++;
//	} while (i <= 10);
//	return 0;
//}

//int main()
//{
//	// 计算1~100之间3的倍数的数字之和
//	int sum = 0;
//	for (int i = 1;i <= 100;i++)
//	{
//		if (i % 3 == 0)
//		{
//			sum += i;
//		}
//	}
//	printf("%d", sum);
//	return 0;
//}

//int main()
//{
//	/* 练习
//找出100~200之间的素数，并打印在屏幕上。
//注：素数⼜称质数，只能被1和本⾝整除的数字。
//题⽬解析
//1. 要从100~200之间找出素数，⾸先得有100~200之间的数，这⾥可以使⽤循环解决。
//2. 假设要判断i是否为素数，需要拿2~i-1之间的数字去试除i，需要产⽣2~i-1之间的数字，也可以使⽤
//循环解决。
//3. 如果2~i-1之间有数字能整除i，则i不是素数，如果都不能整除，则i是素数。*/
//
//	for (int i = 100;i <= 200;i++)
//	{
//		int j = 0;
//		int flag = 1;
//		for (j = 2;j < i;j++)  // 2 ~ i-1
//		{
//			if (i % j == 0) {
//				flag = 0;
//				break;
//			}
//		}
//		if (flag == 1) {
//			printf("%d ", i);
//		}
//	}
//
//	return 0;
//}

//#include <stdio.h>
//int main()
//{
//    int i = 0;
//    // 优化1：从101开始，每次+2，直接跳过所有偶数（100和200之间的偶数全排除）
//    for (i = 101; i <= 200; i += 2)
//    {
//        int flag = 1; // 假设i是素数
//        int j = 0;
//
//        // 优化2：只需要检查到 i 的平方根即可
//        // 这里用 j * j <= i 代替 sqrt(i)，避免引入 math.h 且浮点数运算更快
//        for (j = 3; j * j <= i; j += 2) // 优化3：j 从3开始，只检查奇数因子
//        {
//            if (i % j == 0)
//            {
//                flag = 0;
//                break;
//            }
//        }
//        if (flag == 1)
//            printf("%d ", i);
//    }
//    return 0;
//}

//#include<stdlib.h>
//#include<time.h>

//int main()
//{
//	// 生成随机数
//	//语法：int rand(void);
//	//printf("%d\n", rand());
//	//printf("%d\n", rand());
//	//printf("%d\n", rand());
//	//printf("%d\n", rand());
//	//printf("%d\n", rand());
//
//	// 初始化随机数的生成器（种子）
//	// 语法：void srand(unsigned int seed);
//
//	// 获取时间
//	// 语法：time_t time(time_t * timer);
//	
//	//srand((unsigned int)time(NULL));
//	//printf("%d\n", rand());
//	//printfprintf("%d\n", rand());
//	//printf("%d\n", rand());
//	//printf("%d\n", rand());
//	//printf("%d\n", rand());
//
//
//	return 0;
//}

  /*  ===========  猜数字游戏(简易版)  ==============  */
//void menu()
//{
//	printf("---------------------\n");
//	printf("---     1. play   ---\n");
//	printf("---     0. exit   ---\n");
//	printf("---------------------\n");
//}
//
//void game()
//{
//	int r = rand() % 100 + 1;
//	int guess = 0;
//
//	while (1) {
//		printf("请输入：");
//		scanf("%d", &guess);
//		if (guess < r)
//		{
//			printf("猜小了\n");
//		}
//		else if (guess > r) {
//			printf("猜大了\n");
//		}
//		else {
//			printf("恭喜你，猜对了\n");
//			break;
//		}
//	}
//}
//
//int main()
//{
//	int input = 0;
//	do
//	{
//		menu();
//		printf("请选择：");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//			game();
//			break;
//		case 0:
//			printf("exit\n");
//			break;
//		default:
//			printf("输入错误\n");
//			break;
//		}
//	} while (input);
//	return 0;
//}


#include<string.h>
//int main()

//	// 数组是一组相同类型元素的集合；
//	// 一维数组的语法：type arr_name[常量值]；
//	//char ch[8] = { 0,1,2,3,4,5,6,7 };
//	//int sz = sizeof(ch) / sizeof(ch[0]);
//	//char* p = &ch;
//
//	//for (int i = 0;i < sz;i++)
//	//{
//	//	//printf("%d ", ch[i]);   // 普通求数组元素的值
//	//	printf("%zu ", *(p + i));
//	//}
//
//	char arr1[] = "abc";
//	char arr2[] = { 'a','b','c' };
//	//printf("%zu\n", strlen(arr1));  // 3
//	//printf("%zu\n", strlen(arr2));   // 36 = 9字节 * 4    ‘\0'
//
//	printf("%zu\n", sizeof(arr1));  // 后面有一个"\0",所以有4
//	printf("%zu\n", sizeof(arr2));  // 数组没有"\0",所以有3
//}


// 编写代码，演⽰多个字符从两端移动，向中间汇聚
#include <stdlib.h>
int main()
{
	char arr1[] = "welcome to bit!!!";  // 创建一个数组
	char arr2[] = "#################";  // ##### 用于初始变量数组
	int left = 0;  // 左侧的一个临界值
	int right = strlen(arr1) - 1;   // 右侧的一个临界值
	printf("%s\n", arr2);
	while (left <= right)  // 循环判断 如果left <= right,就执行
	{
		Sleep(1000);
		arr2[left] = arr1[left];
		arr2[right] = arr1[right];
		left++;
		right--;
		printf("%s\n", arr2);
	}
	return 0;
}