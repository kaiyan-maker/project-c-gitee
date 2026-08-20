#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char arr1[] = "welcome to bit!!!";
	char arr2[] = "#################";
	int left = 0;
	int right = strlen(arr1) - 1;
	printf("%s\n", arr2);
	while (left <= right)
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

int main()
{
	// 二分查找
	char arr[] = { 0,1,2,3,4,5,6,7,8,9 };
	int left = 0;
	int right = sizeof(arr) / sizeof(arr[0]) - 1;
	int key = 7;  // 要查找的数据
	int mid = 0;  // 中间的数据
	int find = 0;

	while (left <= right)
	{
		mid = (left + right) / 2;
		if (arr[mid] > key)
		{
			right = mid - 1;
		}
		else if (arr[mid] < key)
		{
			left = mid + 1;
		}
		else 
		{
			find = 1;
			break;
		}
	}

	if (1 == find)
	{
		printf("找到了：%d\n", mid);
	}
	else {
		printf("找不到\n");
	}
	return 0;
}


int main()
{
	// 二维数组
	// 语法：type arr_name[常量值1][常量值2]
	int arr[3][5] = { 1,2,3,4,5, 2,3,4,5,6, 3,4,5,6,7 };
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 5;j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}

	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 5;j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}

#include<stdlib.h>
#include<time.h>
int main()
{
	// 学⽣名单
	char students[20][10] =
	{
	"张三", "李四", "王五", "赵六", "⼩明",
	"⼩红", "⼩刚", "⼩丽", "⼩华", "⼩强",
	"张伟", "李芳", "王磊", "赵敏", "陈晨",
	"刘洋", "孙丽", "周涛", "吴杰", "郑爽"
	};

	int index1 = 0;
	int index2 = 0;

	// 初始化随机数种子
	srand((unsigned int)time(NULL));
	do 
	{
		index1 = rand() % 20;
		index2 = rand() % 20;
	} while (index1 == index2);

	printf("随机点名结果：\n");
	printf("%d %s\n", index1, students[index1]);
	printf("%d %s\n", index2, students[index2]);

	return 0;
}

//int main()
//{
//	// 变长数组
//	int n = 2;
//	int arr[n];  
//	// 在VS2022/2026上，默认的 msvc 编译器，虽然⽀持⼤部分 C99 的语法，却没有⽀持 C99
//	//中的变⻓数组的语法，没法测试；下⾯是我在gcc编译器上测试，可以看⼀下。
//	return 0;
//}

