// Contact.h - 通讯录的头文件
// 通讯录的本质就是一个顺序表，表里每个元素是一个联系人（peoInfo）
#pragma once

#include<stdio.h>   // 标准输入输出（printf / scanf 等）
#include<string.h>  // 字符串函数（strcmp 等）

// 定义各个字段的最大长度，方便统一修改
#define NAME_MAX 20    // 姓名最大长度
#define GENDER_MAX 10  // 性别最大长度
#define TEL_MAX 20     // 电话最大长度
#define ADDR_MAX 100   // 地址最大长度

// 联系人数据结构
typedef struct personInfo
{
	char name[NAME_MAX];     // 姓名
	char gender[GENDER_MAX]; // 性别
	int age;                 // 年龄
	char tel[TEL_MAX];       // 电话号码
	char addr[ADDR_MAX];     // 住址
}peoInfo;

struct SeqList;  // 前置声明：告诉编译器有这样一个结构体类型
// 通讯录的相关方法 
// 给顺序表类型起一个更贴切的别名：通讯录（Contact）
typedef struct SeqList Contact;
// 通讯录的初始化：初始化底层顺序表
void ContactInit(Contact* con);
// 通讯录的销毁：释放内存
void ContactDesTroy(Contact* con);
// 通讯录的添加数据：录入并添加一个联系人
void ContactAdd(Contact* con);
// 通讯录的删除数据：按姓名删除一个联系人
void ContactDel(Contact* con);
// 通讯录的修改数据：按姓名找到联系人并修改信息
void ContactModify(Contact* con);
// 通讯录的查找数据：按姓名查找并展示一个联系人
void ContactFind(Contact* con);
// 展示通讯录数据：打印出所有联系人
void ContactShow(Contact* con);