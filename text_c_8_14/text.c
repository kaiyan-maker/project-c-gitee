#include<stdio.h>

int main()
{
	// 喝汽水，1瓶汽水1元，2个空瓶可以换一瓶汽水，给20元，可以喝多少汽水（编程实现）。
	int money = 20;   // 20元
	int total = money;  // 一开始直接买20瓶，全部喝掉，总数先记为20 
	int empty = money;  // 喝完这20瓶，手里有20个空瓶

	while (empty >= 2)
	{
		// 1. 拿空瓶去换：能换几瓶？就是空瓶数除以2（只取整数部分）
		int exchage = empty / 2;
		// 2. 喝掉新换来的汽水，累计总数增加
		total = total + exchage;
		 // 3. 计算现在手里还剩多少个空瓶
		//    剩余空瓶 = (上次换完剩下的零头) + (刚才新喝掉的瓶数)
		//    empty % 2 就是除以2剩下的余数（比如5个空瓶换2瓶，就剩1个零头）
		empty = empty % 2 + exchage;
	}

	printf("一共可以喝 %d 瓶汽水。\n", total);

	return 0;
}


/*  初始：total=20，empty=20

第1圈：换10瓶，total=30，empty=0+10=10

第2圈：换5瓶， total=35，empty=0+5=5

第3圈：换2瓶（剩1个零头），total=37，empty=1+2=3

第4圈：换1瓶（剩1个零头），total=38，empty=1+1=2

第5圈：换1瓶（剩0个零头），total=39，empty=0+1=1

此时 empty=1，不满足 >=2，循环结束，打印 39。*/



#include <stdio.h>

int main()
{
	int money = 20;
	int total = money;
	int empty = money;

	while (empty >= 2)
	{
		int exchange = empty / 2;
		total += exchange;
		empty = empty % 2 + exchange;
	}

	// 扩展：如果允许借1个空瓶，且最后恰好剩1个空瓶
	if (empty == 1)
	{
		total += 1;   // 借1个空瓶换1瓶，喝完把空瓶还回去
	}

	printf("如果允许赊账，可以喝 %d 瓶。\n", total); // 输出 40

	return 0;
}