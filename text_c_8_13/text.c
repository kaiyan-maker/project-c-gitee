#include<stdio.h>
#include<stdlib.h>


/*   方法一：   */
int main()
{
	// 使用malloc函数模拟开辟一个3*5的整型二维数组（一次分配连续空间）
	int row = 3;
	int col = 5;

	// 分配一块连续空间，一次性容纳 row * col 个整型
	int* arr = (int*)malloc(row * col * sizeof(int));

	// 检查是否成功
	if (arr == NULL) {
		printf("malloc失败\n");
		return 1;
	}

	// 打印数据，arr[i * col + j] 模拟二维下标访问
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < col;j++)
		{
			arr[i * col + j] = i * col + j + 1;
			printf("%d", arr[i * col + j]);
		}
		printf("\n");
	}

	// 释放内存
	free(arr);
	arr = NULL;

	printf("内存释放成功\n");
	return 0;
}


/*   方法二：  */
int main()
{
	int rows = 3;
	int cols = 5;

	// 第一步：分配一个指针数组
	int** arr = (int**)malloc(rows * sizeof(int*));

	// 判断是否为空指针
	if (arr == NULL) {
		printf("动态内存失败\n");
		return 1;  // 返回错误代码
	}

	// 打印二维数组的数据，并为arr[i]分配一个内存空间（列），如果为NULL,释放之前存储的内存空间
	for (int i = 0;i < rows;i++) {
		arr[i] = (int*)malloc(cols * sizeof(int));

		if (arr[i] == NULL) {
			for (int j = 0;j < i;j++) {
				free(arr[j]);
			}
			free(arr);
			return 1;
		}
	}

	// 打印数据
	for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < cols;j++)
		{
			arr[i][j] = i * cols + j + 1;
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	// 释放内存
	for (int i = 0;i < rows;i++)
	{
		free(arr[i]);
	}

	// 释放内存，并把二维数组，置为NULL(空指针)
	free(arr);
	arr = NULL;

	printf("动态内存释放成功\n");
	return 0;
}