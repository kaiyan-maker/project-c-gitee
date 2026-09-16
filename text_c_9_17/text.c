#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

/* ============================================================
   快速排序（Quick Sort）——用 分治法 排序
   时间：平均 O(n log n)   空间：O(log n)（递归栈深度）
   ============================================================

   整体思路（分治法三步）：
   1. 分：选一个基准值 pivot，把数组分成两半
        左边所有元素 < pivot，右边所有元素 >= pivot
      （这个动作由 partition 函数完成）
   2. 治：对左右两半递归执行同样的过程
   3. 合：无需合并，因为所有操作都是原地交换
   ============================================================ */

/* ------------------------------------------------------------
   partition（分区函数）—— 快排的核心
   作用：把 [left, right] 范围整理成
         [小于 key 的部分] key [大于等于 key 的部分]
   返回：key 归位后的下标
   ------------------------------------------------------------
   详细步骤：
   ① 选基准：key = arr[right]（取最右边的元素做基准）
   ② 遍历 i 从 left 到 right-1：
        - 如果 arr[i] < key（比基准小）：
            交换 arr[left] 和 arr[i]   （把小数挪到"小于区"）
            left++                      （"小于区"边界右移一格）
        - 如果 arr[i] >= key：不动，继续往后扫
   ③ 循环结束后：
        [原left, left-1] 全是 < key 的元素
        [left, right-1]  全是 >= key 的元素
   ④ pivot 归位：交换 arr[left] 和 arr[right]（即 key）
        此时 key 到了最终该待的位置，左边都比它小，右边都比它大
   ⑤ 返回 left（key 的新下标）
   ------------------------------------------------------------ */
int partition(int arr[], int left, int right)
{
	int key = arr[right];          // ① 选基准
	int i = 0;
	for (i = left;i <= right - 1;i++)   // ② 遍历扫描
	{
		if (arr[i] < key)
		{
			int temp = arr[left];   // 交换：把小数扔到左区
			arr[left] = arr[i];
			arr[i] = temp;
			left++;                 // "小于区"边界右移
		}
	}

	int tmp = arr[left];            // ④ pivot 归位
	arr[left] = arr[right];
	arr[right] = tmp;
	return left;                    // ⑤ 返回 key 的下标（不是值！）
}

/* ------------------------------------------------------------
   quicksort（递归排序函数）
   ------------------------------------------------------------
   详细步骤：
   ① 基线条件（递归出口）：
        if (left >= right) 直接 return
        说明这一段最多只有一个元素，天然有序
   ② 调用 partition 拿到基准位置 p
   ③ 递归排左半段：quicksort(arr, left, p-1)
       注意 p 本身已经归位，不参与递归
   ④ 递归排右半段：quicksort(arr, p+1, right)
   ------------------------------------------------------------ */
void quicksort(int arr[], int left, int right)
{
	if (left >= right)              // ① 基线条件，递归出口
		return;
	else
	{
		int p = partition(arr, left, right);  // ② 拿基准位置
		quicksort(arr, left, p - 1);          // ③ 排左边
		quicksort(arr, p + 1, right);         // ④ 排右边
	}
}

int main()
{
	int arr[10] = { 0 };
	int sz = sizeof(arr) / sizeof(arr[0]);   // 数组元素个数
	printf("请输入：");
	for (int i = 0;i < sz;i++)               // 逐个读入
	{
		scanf("%d", &arr[i]);
	}

	int left = 0;        // 左边界 = 第一个下标
	int right = sz - 1;  // 右边界 = 最后一个下标

	quicksort(arr, left, right);   // 调一次即可，内部自己会分区

	for (int i = 0;i < sz;i++)     // 打印排序结果验证
	{
		printf("%d ", arr[i]);
	}
	return 0;
}

/* ============================================================
   复习要点 / 易错点
   ============================================================
   1. partition 返回的是【下标 left】，不是值 key
   2. partition 循环结束后必须做 pivot 归位交换，否则 key 没回原位
   3. 交换要三行完整：中间变量 + 两个交换目标
   4. quicksort 先判断基线条件（left >= right），再递归
   5. 递归边界用 p-1 和 p+1，p 自己不再参与
   6. main 里只调一次 quicksort，不要额外再调 partition

   纸上模拟示例：{5, 3, 8, 1, 9, 2} 范围 [0,5]
   初始：  5  3  8  1  9 | 2      key=2, left=0
   i=0~2: 5、3、8 都不比 2 小      → 不动
   i=3:   1 < 2 → 交换 arr[3]与arr[0] → 1 3 8 5 9 2, left=1
   i=4:   9 不比 2 小              → 不动
   归位：  交换 arr[1]与arr[5] → 1 | 2 | 8 5 9 3
   返回 p=1，再递归排 [0,0] 和 [2,5]
   ============================================================ */