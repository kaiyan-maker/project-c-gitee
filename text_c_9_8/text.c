#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

/*  输⼊⼀个字符串，判断这个字符串是否是回⽂字符串（字符串的⻓度⼩于等于30，字符串不包含空
格），如果是回⽂字符串输出Yes，如果不是回⽂字符串输出No。  */
/*int is_primed_arr(char arr[])
{
	// 获取字符串长度
	int len = strlen(arr);
	// 定义两个指针，分别指向字符串的首位和末尾
	char* left = arr;
	char* right = arr + len - 1;
	// 使用循环去判断回文字符串
	while (left < right)
	{
		if (*left != *right)
			return 0;
		left++;
		right--;
	}
	return 1;
}

int main()
{
	char arr[31] = { 0 };
	scanf("%s", &arr);

	int ret  = is_primed_arr(arr);
	
	if (ret == 1)
		printf("Yes\n");
	else
		printf("No\n");

	return 0;
}*/

/*  输⼊y和m两个整数，y表⽰年份，m表⽰⽉份，计算y年m⽉有多少天，并输出天数。  */
/*int is_year_month(int* y,int* m)
{
	//将每个⽉份的天数记录在数组中
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// 获取月份的天数
	int day = days[*m];

	// 判断2月的天数
	if ((*y % 4 == 0 && *y % 100 != 0) || (*y % 400 == 0))
	{
		// 判断是否为2月
		if (m == 2)
			day += 1;
	}

	// 返回输出的天数
	return day;
}

int main()
{
	// 1.输入两个整数，一个作为年份，一个作为月份
	int y = 0;
	int m = 0;
	scanf("%d-%d", &y, &m);

	int ret = is_year_month(&y, &m);

	printf("%d", ret);
	return 0;
}*/

/*  先输⼊10个整数存放在数组中，再输⼊⼀个整数n，删除数组中所有等于n的数字，数组中剩余的数
组保证数组的最前⾯，打印剩余的数字。注：m的  */
/*int main()
{
	int arr[10] = { 0 };
	int del = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);
	
	// 输入
	for (int i = 0;i < sz;i++) {
		scanf("%d", &arr[i]);
	}
	scanf("%d", &del);
	
	// 删除数组中所有等于n的数字
	int j = 0;
	for (int i = 0;i < sz;i++)
	{
		if (arr[i] != del)
		{
			arr[j++] = arr[i];
		}
	}

	// 输出
	for (int i = 0;i < j;i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}*/

/*  写⼀个函数my_strcpy，实现拷⻉字符串的功能，假设给定⼀个字符数组a，再给定⼀个字符数组
b，将字符串a中的内容拷⻉到字符串b中，拷⻉内容包含字符串末尾的 \0 字符。  */
/*void my_strcpy(char* dest,const char* src)
{
	while (*src == '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
}

int main()
{
	char arr1[] = "hello bit!!!";
	char arr2[30] = "";

	// 模拟strcpy 的实现
	strcpy(arr2, arr1);

	printf("%s", arr2);
	return 0;
}*/

/*  输⼊两个升序排列的序列，将两个序列合并为⼀个有序序列并输出。
输⼊包含三⾏，第⼀⾏包含两个正整数n, m，⽤空格分隔。n表⽰第⼆⾏第⼀个升序序列中数字的个
数，m表⽰第三⾏第⼆个升序序列中数字的个数。其中
1<=n<=30, 1<=m<=30 第⼆⾏包含 n 个整数，⽤空格分隔。
第三⾏包含 m 个整数，⽤空格分隔。
输出为⼀⾏，输出⻓度为n+m的升序序列，即⻓度为n的升序序列和⻓度为m的升序序列中的元素重
新进⾏升序序列排列合并。  */

/*  合并两个升序序列为一个有序序列  */
int main()
{
	// 1.定义两个序列的长度
	int n = 0;
	int m = 0;
	// 2.输入两个序列的长度
	scanf("%d", &n);
	scanf("%d", &m);
	// 3.定义两个输入数组和一个结果数组
	int arr1[10] = { 0 };
	int arr2[10] = { 0 };
	int arr3[20] = { 0 };
	// 4.输入第一个升序序列的元素
	for (int i = 0;i < n;i++)
	{
		scanf("%d", &arr1[i]);
	}
	// 5.输入第二个升序序列的元素
	for (int i = 0;i < m;i++)
	{
		scanf("%d", &arr2[i]);
	}
	// 6.i 遍历 arr1，j 遍历 arr2，k 遍历 arr3（结果数组）
	int i = 0;
	int j = 0;
	int k = 0;
	// 7.双指针合并：逐一比较两个序列的当前元素，将较小的放入结果数组
	while (i < n && j < m)
	{
		if (arr1[i] < arr2[j])
		{
			arr3[k] = arr1[i];
			i++;
			k++;
		}
		else {
			arr3[k] = arr2[j];
			j++;
			k++;
		}
	}
	// 8.如果 arr1 已经遍历完，将 arr2 剩余元素全部拷贝到 arr3
	if (i == n)
	{
		for (;j < m;j++)
		{
			arr3[k] = arr2[j];
			k++;
		}
	}
	// 9.如果 arr2 已经遍历完，将 arr1 剩余元素全部拷贝到 arr3
	if (j == m)
	{
		for (;i < n;i++)
		{
			arr3[k] = arr1[i];
			k++;
		}
	}
	// 10.输出合并后的升序序列
	for (k = 0;k < n + m;k++)
	{
		printf("%d ", arr3[k]);
	}
	return 0;
}