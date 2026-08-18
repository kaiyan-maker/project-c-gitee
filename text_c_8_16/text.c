#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//int main()
//{
//	// 输⼊⼀个整数，判断是否为奇数
//	int n = 0;
//	printf("请输入整数：");
//	scanf("%d", &n);
//
//	if (n % 2 == 1)
//	{
//		printf("偶数");
//	}
//	else {
//		printf("奇数");
//	}
//	return 0;
//}

//int main()
//{
//	// 输⼊⼀个成绩，成绩 >= 60就输出：拿捏拿捏，否则就输出：补考补考
//	double scou = 0;
//	printf("请输入：");
//	scanf("%lf", &scou);
//
//	if (scou >= 60) 
//	{
//		printf("拿捏拿捏\n");
//	}
//	else {
//		printf("补考补考\n");
//	}
//	return 0;
//}

//int main()
//{
//	// 总价“满50减15，满30减8，满20减5，不满20元，不参与活动”，怎么实现？
//	int total = 0;
//	printf("请输入：");
//	scanf("%d", &total);
//
//	if (total >= 50) {
//		printf("满50减15：%d",total - 15);
//	}
//	else if (total >= 30) {
//		printf("满30减8: %d", total - 8);
//	}
//	else if (total >= 20) {
//		printf("满20减5: %d", total - 5);
//	}
//	else {
//		printf("不满20元，不参与活动");
//	}
//	return 0;
//}

//int main()
//{
//	/*  练习：暗恋对象回消息速度和⼼情指数
//	如果回复时间⼩于1分钟，秒回！今天⼀定有戏
//	如果回复时间在1分钟到10分钟，还⾏，ta可能在忙
//	如果回复时间在10分钟到1⼩时，ta可能没看到信息……我去打游戏了
//	如果回复时间超过1⼩时，别等了，代码不⾹吗？ */
//
//	int min = 0;
//	printf("请输入：");
//	scanf("%d", &min);
//
//	if (min <= 1) {
//		printf("秒回！今天⼀定有戏\n");
//	}
//	else if (min > 1 && min <= 10) {
//		printf("还⾏，ta可能在忙\n");
//	}
//	else if (min > 10 && min <= 60) {
//		printf("ta可能没看到信息……我去打游戏了\n");
//	}
//	else {
//		printf("别等了，代码不香吗\n");
//	}
//	return 0;
//}

//int main()
//{
//	/*  评奖学⾦资格
//	1. 成绩 >= 85，没有挂科，没有记过处分，有奖学⾦
//	2. 其中任意⼀个条件不满⾜，都不能评奖
//	怎么实现呢？*/
//
//	int score = 0;
//	int has_fail = 0; // 0没挂科
//	int has_warn = 0; // 0没处分
//	printf("请输入：");
//	scanf("%d", &score);
//
//	if (score >= 85) {
//		if (has_fail == 0) {
//			if (has_warn == 0) {
//				printf("有奖学金\n");
//			}
//			else {
//				printf("有处分\n");
//			}
//		}
//		else {
//			printf("有挂科\n");
//		}
//	}
//	else {
//		printf("成绩不合格\n");
//	}
//	return 0;
//}

//int main()
//{
//	/*  输⼊⼀个年份year，判断year是否是闰年
//	闰年判断的规则：
//	1. 能被4整除并且不能被100整除是闰年
//	2. 能被400整除是闰年  */
//	int year = 0;
//	scanf("%d", &year);
//
//	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
//	{
//		printf("闰年\n");
//	}
//	else 
//	{
//		printf("平年\n");
//	}
//	return 0;
//}

//int main()
//{
//	// 游戏中，同时持有 ‘钥匙’ 且 ⾎量>30%，或被诅咒了，才能进⼊隐藏房间。 
//	int has_key = 1; //是否有钥匙
//	int hp = 25; //⾎量
//	int is_cursed = 1; //是否被诅咒
//
//	if ((has_key && hp > 30) || is_cursed)
//	{
//		printf("打开诅咒之屋\n");
//	}
//	else{
//		printf("进不去\n");
//	}
//	return 0;
//}

int main()
{
	// 输⼊任意⼀个整数值，计算除3之后的余数
	int n = 0;
	scanf("%d", &n);

	//if (n % 3 == 0) {
	//	printf("余数是0");
	//}
	//else if (n % 3 == 1){
	//	printf("余数是1");
	//}
	//else {
	//	printf("余数是2");
	//}

	switch (n % 3)
	{
	case 0:
		printf("余数是0\n");
		break;
	case 1:
		printf("余数是1\n");
		break;
	case 2:
		printf("余数是2\n");
		break;
	default:
		printf("输入错误，请重新输入\n");
		break;
	}
	return 0;
}