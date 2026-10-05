#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NAME_MAX 100
#define SEX_MAX 4
#define TEL_MAX 12
#define ADDR_MAX 100
#define NUMBER_MAX 16
//前置声明
typedef struct SListNode contact;
//⽤⼾数据
typedef struct PersonInfo
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tel[TEL_MAX];
	char addr[ADDR_MAX];
}PeoInfo;
//初始化通讯录
void InitContact(contact** con);//实际调⽤的是链表的初始化接⼝（可以简单做⼀个头结点的初始化）
//添加通讯录数据
void AddContact(contact** con);// 链表尾插/头插
//删除通讯录数据
void DelContact(contact** con);//链表的删除指定位置的数据
//展⽰通讯录数据
void ShowContact(contact* con);//链表的打印
//查找通讯录数据
void FindContact(contact* con);
//修改通讯录数据
void ModifyContact(contact** con);
//销毁通讯录数据
void DestroyContact(contact** con);
//通讯录菜单（程序入口的交互部分）
void ContactMenu(void);