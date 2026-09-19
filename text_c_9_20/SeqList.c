// SeqList.c - 动态顺序表的实现
// 这里实现的每个函数，都对应 SeqList.h 中声明的接口
#include "SeqList.h"

// 顺序表的初始化
// 参数 ps：指向要初始化的顺序表
void SLInit(SL* ps)
{
	ps->arr = NULL;   // 数组指针先置为空，还没申请内存
	ps->size = ps->capacity = 0;  // 数据个数和容量都初始化为 0
}

// 顺序表的销毁
// 作用：释放顺序表动态申请的内存，防止内存泄漏
void SLDestroy(SL* ps)
{
	// 如果数组指针不为空，说明申请过内存，需要释放
	if (ps->arr)
	{
		free(ps->arr);
	}
	// 防止野指针，释放后把指针置空，并把数据个数和容量归零
	ps->arr = NULL;
	ps->size = ps->capacity = 0;
}

// 检查容量，空间不够时自动扩容
// 作用：保证插入数据前一定有足够的空间
void SLCheckCapacity(SL* ps)
{
	// 先看空间够不够（容量 == 个数 说明已经满了）
	if (ps->capacity == ps->size)
	{
		// 申请内存空间
		// 如果是第一次扩容（容量为 0），先给 4 个空间；否则容量翻倍
		int newCapacity = ps->capacity == 0 ? 4 : 2 * ps->capacity;
		// realloc：在原空间的基础上扩容，并保留原来的数据
		SLDateType* tmp = (SLDateType*)realloc(ps->arr, newCapacity * sizeof(SLDateType));
		// 判断空间是否申请成功
		if (tmp == NULL)
		{
			perror("realloc fail!");  // 打印失败原因
			exit(1);  // 直接退出程序，不再执行
		}
		// 空间申请成功，更新数组指针和容量
		ps->arr = tmp;
		ps->capacity = newCapacity;
	}
}

// 尾插：在顺序表末尾插入数据 x
void SLPushBack(SL* ps, SLDateType x)
{
	// 判断指针是否为空
	/*if (ps == NULL)
		return;*/
	assert(ps);  // 断言 --> assert(ps != NULL)，传参不能为空
	SLCheckCapacity(ps);   // 先检查容量，不够就扩容
	ps->arr[ps->size++] = x;  // 把数据放到 size 位置，然后 size 加 1

}

// 头插：在顺序表开头插入数据 x
void SLPushFront(SL* ps, SLDateType x)
{
	assert(ps);   // 断言 ps 不为空
	SLCheckCapacity(ps);  // 检查容量
	// 先让顺序表整体往后挪一位，空出下标 0 的位置
	for (int i = ps->size;i > 0;i--)
	{
		ps->arr[i] = ps->arr[i - 1];  // 从最后一个元素开始，依次后移
	}
	ps->arr[0] = x;   // 把新数据放到表头
	ps->size++;       // 数据个数加 1
}

//void SLPrint(SL s)
//{
//	for (int i = 0;i < s.size;i++)
//	{
//		printf("%d ", s.arr[i]);
//	}
//	printf("\n");
//}

// 尾删：删除顺序表末尾的一个数据
void SLPopBack(SL* ps)
{
	assert(ps);
	// 判断顺序表是否为空（为空就不能删）
	assert(ps->size);
	// 顺序表不为空
	//ps->arr[ps->size - 1] = -1;
	--ps->size;  // 直接让 size 减 1，末尾数据就算被删除了
}

// 头删：删除顺序表开头的一个数据
void SLPopFront(SL* ps)
{
	assert(ps);
	assert(ps->size);  // 顺序表不能为空
	// 把后面的数据依次往前挪一位，覆盖掉开头的数据
	for (int i = 0;i < ps->size-1;i++)
	{
		ps->arr[i] = ps->arr[i + 1];
	}
	ps->size--;  // 数据个数减 1
}

// 在指定位置之前插入数据
// 参数 pos：插入的位置（0 <= pos <= size）
void SLInSert(SL* ps, int pos, SLDateType x)
{
	assert(ps);
	// 位置必须在合法范围内：不能小于 0，也不能超过当前有效长度
	assert(pos >= 0 && pos <= ps->size);
	// 申请空间：不够就扩容
	SLCheckCapacity(ps);
	// 让pos之后的数据整体往后挪，空出 pos 的位置
	for (int i = ps->size;i > pos;i--)
	{
		ps->arr[i] = ps->arr[i - 1];  // arr[pos+1] = arr[pos]
	}
	ps->arr[pos] = x;  // 在空出的位置放入新数据
	ps->size++;        // 数据个数加 1
}

// 删除指定位置的数据
// 参数 pos：要删除的位置（0 <= pos < size）
void SLErase(SL* ps, int pos)
{
	assert(ps);
	// 位置必须在合法范围内：要删除的必须是已存在的元素
	assert(pos >= 0 && pos < ps->size);
	// 把 pos 之后的数据整体往前挪一位，覆盖掉 pos 位置的数据
	for (int i = pos;i < ps->size-1;i++)
	{
		ps->arr[i] = ps->arr[i + 1];  // arr[size-2] = arr[size-1] 
	}
	ps->size--;  // 数据个数减 1
}

 //顺序表的查找
/*int SLFind(SL* ps, SLDateType x)
{
	assert(ps);
	for (int i = 0;i < ps->size;i++)
	{
		if (ps->arr[i] == x)
		{
			return i;
		}
	}
	return -1;  // 没有找到
}*/