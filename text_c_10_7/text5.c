#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

#define MAX_STU 100   //最多存100个学生

//学生结构体
typedef struct {
    int id;         //学号
    char name[20];  //姓名
    int score;      //分数
} Student;

Student stu[MAX_STU];
int count = 0; //当前学生数量

//菜单
void menu() {
    printf("\n=====学生成绩管理系统=====\n");
    printf("1.录入学生信息\n");
    printf("2.冒泡排序（分数升序）\n");
    printf("3.选择排序（学号升序）\n");
    printf("4.快速排序（分数降序）\n");
    printf("5.显示所有学生\n");
    printf("0.退出\n");
    printf("请输入功能选择：");
}

//录入学生
void inputStu() {
    printf("请输入学生学号 姓名 分数（一行一个，输入-1结束录入）\n");
    while (1) {
        printf("第%d个学生：", count + 1);
        scanf("%d", &stu[count].id);
        if (stu[count].id == -1) break; //输入-1停止录入
        scanf("%s %d", stu[count].name, &stu[count].score);
        count++;
        if (count >= MAX_STU) {
            printf("人数已满！\n");
            break;
        }
    }
}

//打印全部学生
void printStu() {
    printf("\n学号\t姓名\t分数\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%d\n", stu[i].id, stu[i].name, stu[i].score);
    }
}

//冒泡排序：按分数从小到大
void bubbleSort() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (stu[j].score > stu[j + 1].score) {
                //交换两个结构体
                Student temp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = temp;
            }
        }
    }
}

//选择排序：按学号从小到大
void selectSort() {
    int minIdx;
    for (int i = 0; i < count - 1; i++) {
        minIdx = i;
        for (int j = i + 1; j < count; j++) {
            if (stu[j].id < stu[minIdx].id) {
                minIdx = j;
            }
        }
        Student temp = stu[i];
        stu[i] = stu[minIdx];
        stu[minIdx] = temp;
    }
}

//快速排序：按分数从大到小
void quickSort(int left, int right) {
    if (left >= right) return;
    Student pivot = stu[left];
    int l = left, r = right;
    while (l < r) {
        while (l < r && stu[r].score <= pivot.score) r--;
        stu[l] = stu[r];
        while (l < r && stu[l].score >= pivot.score) l++;
        stu[r] = stu[l];
    }
    stu[l] = pivot;
    quickSort(left, l - 1);
    quickSort(l + 1, right);
}

int main() {
    int op;
    while (1) {
        menu();
        scanf("%d", &op);
        switch (op) {
        case 1: 
            inputStu(); 
            break;
        case 2: 
            bubbleSort(); 
            printf("【冒泡排序完成：按分数升序】\n"); 
            break;
        case 3: 
            selectSort(); 
            printf("【选择排序完成：按学号升序】\n"); 
            break;
        case 4: 
            quickSort(0, count - 1); 
            printf("【快速排序完成：按分数降序】\n"); 
            break;
        case 5: 
            printStu(); 
            break;
        case 0: 
            printf("程序退出\n"); 
            return 0;
        default: printf("输入错误！\n");
        }
    }
    return 0;
}