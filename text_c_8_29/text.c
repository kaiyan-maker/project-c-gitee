#define	_CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<ctype.h>

/* 字符和字符串函数  */
int main()
{
	//int islower(int c);

	// 写⼀个代码，将字符串中的⼩写字⺟转⼤写，其他字符不变。
	char str[] = "Test String.\n";
	char c = 0;
	int i = 0;
	while (str[i])
	{
		c = str[i];
		if (islower(c))
		{
			c -= 32;
		}
		putchar(c);
		i++;
	}
	return 0;
}

#include<string.h>

size_t my_strlen(const char* str)
{
	if (*str == "\0")
		return 0;
	else
		return 1 + my_strlen(str + 1);
}
int main()
{
	// 语法：size_t strlen(const char* str);
	const char* str = "abcdef";
	//printf("%zd\n", strlen(str));
	size_t p = my_strlen(str);
	printf("%zd\n", p);
	return 0;
}

char* my_strcpy(char* dest,char* sour)
{
	char* ret = dest;
	while (*dest++ == *sour++)
	{
		;
	}
	return ret;
}

int main()
{
	// 语法：char* strcpy(char* dest, const char* source);
	char arr1[10] = { 0 };
	char arr2[] = "hello";
	//strcpy(arr1, arr2);
	char* p = my_strcpy(arr1, arr2);
	printf("%s\n", p);
	

	return 0;
}

char* my_strcat(char* dest,char* sour)
{
	char* ret = dest;
	while (*dest)
	{
		dest++;
	}
	while ((*dest++ == *sour++))
	{
		;
	}
	return ret;
}

int main()
{
	// 语法：char* strncpy(char* dest, const char* sour, size_t num);
	// 语法： char* strcat(char* dest,const char* sour);
	char arr1[20] = "hello";
	char arr2[] = "world";
	my_strcat(arr1, arr2);
	printf("%s\n", arr1);
	return 0;
}

int my_strcmp(const char* str1, const char* str2)
{
	int ret = 0;
	assert(str1 != NULL);
	assert(str2 != NULL);
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	
	return (unsigned char)*str1 - (unsigned char)*str2;
}

int main()
{
	// 语法： int strcmp ( const char * str1, const char * str2 );
	char arr1[] = "abc";
	char arr2[] = "def";
	my_strcmp(arr1, arr2);
	return 0;
}