#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------------------------------------------
// 顺序表是什么？用最简单的话说：
//    顺序表 = 一块连续的内存空间（就像一排编号固定的抽屉）+ 记录信息的两个数。
//    我们平时写的 int arr[100] 就是一个"容量固定"的顺序表雏形，
//    好处是能直接按下标访问，坏处是装满了就装不下了。
//    所以下面的写法把它升级成"动态的"：满了就自动换更大的空间。
// ------------------------------------------------------------------

// SLDataType：给 int 起个"外号"。
// 万一以后想存 double、char，只需要改这一处，其它代码都不用动。
typedef int SLDataType;

typedef struct SeqList
{
	SLDataType* a;   // 一个指针，指向真正存放数据的那块连续内存（可以把它想象成"抽屉柜"）
	int size;        // 现在"抽屉"里已经装了几个有效元素（等于已用格子数）
	int capacity;    // 柜子总共能装多少个元素（等于格子总数）
} SL;

// ==================================================================
// 下面只是"声明"每个函数长什么样子，具体怎么实现写在 SeqList.c 里。
// 这样能把"接口长啥样"和"内部怎么实现"分开，代码更清晰。
// ==================================================================

// ---- 基本 ----
void SLInit(SL* ps);          // 初始化：把顺序表"开箱"
void SLDestroy(SL* ps);       // 销毁：用完归还内存

// ---- 增（Add）----
void SLPushBack(SL* ps, SLDataType x);   // 尾插：从末尾加一个
void SLPushFront(SL* ps, SLDataType x);  // 头插：从开头加一个
void SLInsert(SL* ps, int pos, SLDataType x); // 任意位置插入

// ---- 删（Delete）----
void SLPopBack(SL* ps);       // 尾删：删掉最后一个
void SLPopFront(SL* ps);      // 头删：删掉第一个
void SLErase(SL* ps, int pos); // 删除指定位置

// ---- 查（Search）----
int SLFind(SL* ps, SLDataType x);  // 查找某个值，找到返回下标，找不到返回 -1

// ---- 打印（Show）----
void SLPrint(SL* ps);         // 把顺序表里所有元素打印出来