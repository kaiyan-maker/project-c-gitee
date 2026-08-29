#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//int main()
//{
//	FILE* src, * dst;
//	char ch = 0;
//	// 1.打开文件data.txt，读
//	src = fopen("data.txt", "r");
//
//	if (src == NULL)
//	{
//		printf("写入错误\n");
//		return 1;
//	}
//	// 2.打开文件data_copy.txt,写
//	dst = fopen("data_copy", "w");
//
//	if (dst == NULL)
//	{
//		printf("读取错误\n");
//		fclose(src);
//		return 1;
//	}
//	// 3.从data.txt中读取数据存放到data_copy.txt文件中，直到文件结束
//	while ((ch == fgetc(src)) != EOF)
//	{
//		fputc(ch,dst);
//	}
//	// 4.关闭文件
//	fclose(src);
//	fclose(dst);
//
//	printf("拷贝完成：data.txt -> data_copy.txt\n");
//	return 0;
//}

//#include <stdio.h>
//#include<stddef.h>
//
//#define OFFSETOF(type, member)  ((size_t)&(((type *)0)->member))
//
//// 测试用的结构体
//typedef struct {
//    char a;      // 通常偏移 0
//    int b;       // 通常偏移 4（考虑对齐）
//    double c;    // 通常偏移 8 或 16（考虑对齐）
//    char d[10];  // 通常偏移 16 或 24
//} TestStruct;
//
//int main() {
//    printf("结构体 TestStruct 各成员的偏移量：\n");
//    printf("a 的偏移量 = %zu\n", OFFSETOF(TestStruct, a));
//    printf("b 的偏移量 = %zu\n", OFFSETOF(TestStruct, b));
//    printf("c 的偏移量 = %zu\n", OFFSETOF(TestStruct, c));
//    printf("d 的偏移量 = %zu\n", OFFSETOF(TestStruct, d));
//    printf("整个结构体大小 = %zu\n", sizeof(TestStruct));
//
//    // 验证：用 C 标准库的 offsetof 对比（需要 stddef.h）
//    // printf("标准库 offsetof 验证：%zu\n", offsetof(TestStruct, b));
//
//    return 0;
//}

#include <stdio.h>

// 32位整数奇偶位交换宏
#define SWAP_ODD_EVEN_BITS(x)  (((x) & 0xAAAAAAAA) >> 1) | (((x) & 0x55555555) << 1)

// 打印二进制（辅助函数，便于观察结果）
void print_binary(unsigned int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) printf(" ");  // 每4位加空格，便于阅读
    }
    printf("\n");
}

int main() {
    unsigned int test_values[] = {
        0xAAAAAAAA,  // 全部奇数位为1
        0x55555555,  // 全部偶数位为1
        0x12345678,  // 随机值
        0xFFFFFFFF,  // 全1
        0x00000000   // 全0
    };

    for (int i = 0; i < 5; i++) {
        unsigned int original = test_values[i];
        unsigned int swapped = SWAP_ODD_EVEN_BITS(original);

        printf("原始值:  0x%08X  ", original);
        print_binary(original);
        printf("交换后:  0x%08X  ", swapped);
        print_binary(swapped);
        printf("\n");
    }

    return 0;
}