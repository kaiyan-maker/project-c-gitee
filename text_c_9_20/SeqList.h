// SeqList.h - 动态顺序表的头文件
// 顺序表：用一段连续的内存空间依次存储数据，
// 支持在任意位置插入、删除、查找等操作（类似数组，但容量可以动态增长）
#pragma once

// 标准输入输出头文件（printf / scanf 等）
#include<stdio.h>
// 标准库内存管理头文件（malloc / realloc / free 等）
#include<stdlib.h>
// 断言头文件（assert）
#include<assert.h>
// 引入联系人数据结构，顺序表里存放的数据就是一个一个的联系人
#include "Contact.h"

#define N 100  // 静态顺序表的最大容量（当前未使用）

// 静态顺序表：固定大小的数组，容量不可改变（已弃用，仅作对比参考）
//struct SeqList
//{
//	int arr[N];
//	int size;  // 有效数据个数
//};

//typedef int SLDateType;          // 曾用：数据类型是 int
typedef peoInfo SLDateType;        // 现用：数据类型是联系人结构体 peoInfo

// 动态顺序表：内存不够用时自动扩容
typedef struct SeqList
{
	SLDateType* arr;    // 指向堆区动态开辟的连续数组空间（首地址）
	int size;           // 数据个数（当前有效元素的个数）
	int capacity;       // 空间大小（当前一共最多能存放多少个元素）
}SL;

//顺序表的初始化：把数组指针置空，size 和 capacity 清 0
void SLInit(SL* ps);
// 顺序表的销毁：释放动态申请的内存空间
void SLDestroy(SL* ps);

// 打印顺序表（当前未使用，暂保留声明）
void SLPrint(SL s);
// 顺序表的插入数据,头插/尾插
void SLPushBack(SL* ps, SLDateType x);   // 尾插：在表尾插入一个新数据
void SLPushFront(SL* ps, SLDateType x);  // 头插：在表头插入一个新数据

void SLPopBack(SL* ps);   // 尾删：删除表尾的一个数据
void SLPopFront(SL* ps);  // 头删：删除表头的一个数据
// 顺序表的添加/删除数据（指定位置操作）
void SLInSert(SL* ps, int pos, SLDateType x);  // 在 pos 位置之前插入数据
void SLErase(SL* ps, int pos);                 // 删除 pos 位置的数据
int SLFind(SL* ps, SLDateType x);              // 查找数据（当前未使用，暂保留声明）