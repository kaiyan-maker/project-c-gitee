#include<stdio.h>
#include<stdlib.h>

/*  贪心算法  */
int cmp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int findContentChlldren(int* g, int gSize, int* s, int sSize)
{
	// 1. 对孩子胃口数组升序排序
	qsort(g, gSize, sizeof(int), cmp);
	// 2. 对饼干大小数组升序排序
	qsort(s, sSize, sizeof(int), cmp);

	int i = 0;  // 指向当前待喂饱的孩子
	int j = 0;  // 指向当前正在尝试使用的饼干

	// 遍历所有孩子和饼干，直到其中一方遍历完毕
	while (i < gSize && j < sSize)
	{
		// 当前饼干能喂饱当前孩子。切换到下一个孩子
		if (s[j] >= g[i])
		{
			i++;  // 孩子数量加1，（已喂饱）
		}
		j++;  // 无论饼干是否可用，都切换到下一块饼干
	}

	return i;  // 已喂饱的孩子总数
}

int main()
{
	int g[] = { 1,2,3 };  // 孩子胃口数组
	int s[] = { 1,1 };   // 饼干大小数组

	printf("最多能喂饱的孩子数量：%d\n", findContentChlldren(g, 3, s, 2));

	return 0;
}