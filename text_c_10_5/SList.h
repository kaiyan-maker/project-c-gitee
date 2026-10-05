#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

/* 下面几个宏用于"模板复用"：包含本头文件之前用 #define 覆盖它们，
   就能让同一份链表实现服务于不同的数据域类型（默认是 int） */
#ifndef SLIST_TYPE                 // 数据域类型
#define SLIST_TYPE int
#endif
#ifndef SLIST_PRINT_DATA           // 打印数据域的方式
#define SLIST_PRINT_DATA(data) printf("%d ", (data))
#endif
#ifndef SLIST_CMP_DATA             // 比较数据域是否命中
#define SLIST_CMP_DATA(data, x) ((data) == (x))
#endif

/* 复用时如果定义 SLIST_STATIC，这批接口就只服务于当前源文件，不对外暴露 */
#ifdef SLIST_STATIC
#define SLIST_API static
#else
#define SLIST_API extern
#endif

typedef SLIST_TYPE SLDataType;

typedef struct SListNode
{
	SLDataType data;
	struct SListNode* next;   // 指向下一节点的指针
}SLTNode;

// 链表的打印
SLIST_API void SLTPrint(SLTNode* phead);

// 头部插入删除/尾部插入删除
SLIST_API void SLTPushBack(SLTNode** pphead, SLDataType x);
SLIST_API void SLTPushFront(SLTNode** pphead, SLDataType x);
SLIST_API void SLTPopBack(SLTNode** pphead);
SLIST_API void SLTPopFront(SLTNode** pphead);

// 查找
SLIST_API SLTNode* SLTFind(SLTNode* phead, SLDataType x);
// 在指定位置之前插入数据
SLIST_API void SLTInsert(SLTNode** pphead, SLTNode* pos, SLDataType x);
// 删除pos节点
SLIST_API void SLTErase(SLTNode** pphead, SLTNode* pos);
// 在指定位置之后插入数据
SLIST_API void SLTInsertAfter(SLTNode* pos, SLDataType x);
// 删除pos之后的节点
SLIST_API void SLTEraseAfter(SLTNode* pos);
// 销毁链表
SLIST_API void SListDesTroy(SLTNode** pphead);