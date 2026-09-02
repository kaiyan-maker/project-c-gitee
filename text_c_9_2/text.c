#include<stdio.h>

/*  输⼊10个整数，然后使⽤冒泡排序对数组内容进⾏升序排序，然后打印数组的内容  */
void Frb(int arr[], int sz)
{
	for (int i = 0;i < sz - 1;i++)
	{
		for (int j = 0;j < sz - i - 1;j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

void Print(int arr[],int sz)
{
	for (int i = 0;i < sz;i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	int num = 0;
	int arr[10] = { 0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0;i < sz;i++)
	{
		scanf_s("%d", &arr[i]);
	}

	Frb(arr,sz);
	
	Print(arr,sz);
	return 0;
}

/* 某地发⽣了⼀件盗窃案，警察通过排查确定盗窃者必为4个嫌疑⼈的⼀个。
以下为4个嫌疑⼈的供词:
A说：不是我。
B说：是C。
C说：是D。
D说：C在胡说
已知3个⼈说了真话，1个⼈说的是假话。
现在请根据这些信息，写⼀个程序来确定到底谁是盗窃者。*/
int main()
{
	char thicher = 0;
	for (char thicher = 'a';thicher < 'd';thicher++)
	{
		if ((thicher != 'a') + (thicher == 'c') + (thicher == 'd') + (thicher != 'd') == 3)
		{
			printf("盗窃者：%c", thicher);
		}
	}
	return 0;
}