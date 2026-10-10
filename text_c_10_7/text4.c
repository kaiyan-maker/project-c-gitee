//#include<stdio.h>
//
////int Frb(int i)
////{
////	if (i == 0)
////		return 1;
////	return i * Frb(i - 1);
////}
////
////int main()
////{
////	int i = 0;
////	scanf_s("%d", &i);
////
////	int p = Frb(i);
////	printf("%d\n", p);
////	return 0;
////}
//
//int Frb(int i)
//{
//	if (i == 0)
//		return 0;
//	else if (i == 1)
//		return 1;
//	return Frb(i - 1) + Frb(i - 2);
//}
//
//int main()
//{
//	int i = 0;
//	scanf_s("%d", &i);
//
//	int p = Frb(i);
//	printf("%d\n", p);
//	return 0;
//}