#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

//int BF(const char* s1, const char* s2)
//{
//	int i = 0; int j = 0;
//	int len1 = strlen(s1);
//	int len2 = strlen(s2);
//	for (i = 0; i < len1;)
//	{
//		while (s1[i] == s2[j]&&s1[i]!='\0')
//		{
//			i++;
//			j++;
//		}
//		if (j < len2)
//		{
//			j = 0;
//			i = i - j+1;
//		}
//		else
//			return i-j;
//	}
//	return -1;
//}
/////////////↑暴力算法


void getNext(const char *s,int *next,const int len)//const增强程序健壮性
{
	next[0] = -1;
	next[1] = 0;
	int i = 2;
	int k = 0;
	for (; i < len;)
	{
		if (k==-1||s[k] == s[i - 1])
		{
			next[i] = k + 1;
			i++;
			k++;
		}
		else
		{
			k = next[k];
		}
	}
}


void getNextval(const char* s, const int* next, const int len, int* nextval)
{
	nextval[0] = -1;
	int i = 1;
	for (; i < len; i++)
	{
		if (s[next[i]] == s[i])
		{
			nextval[i] = next[next[i]];
		}
		else
		{
			nextval[i] = next[i];
		}
	}
}


int KMP(const char* s1, const char* s2, int pos)//KMP主要是主串下标不回调，所以效率更高
{
	assert(s1 && s2);//断言确定两个不是空指针
	int len1 = strlen(s1);//主串长度
	int len2 = strlen(s2);//匹配串长度
	if (len1 == 0 || len2 == 0)
		return -1;//任意一个串长度为0则此功能没有实现的意义
	if (pos < 0 || pos >= len1)
		return -1;//如果主串下标越界，则传参有问题
	int* next = (int*)malloc(sizeof(int) * len2);//开辟一个next数组
	getNext(s1,next,len2);
	int* nextval = (int*)malloc(sizeof(int) * len2);//优化next
	getNextval(s1,next,len2,nextval);
	int i = pos; int j = 0;
	while (i < len1 && j < len2)//循环的限度，不会超出两个字符串任意一个的长度
	{
		if (j == -1 || s1[i] == s2[j])//如果匹配串首字符匹配不成功，将会返回j值-1，此时i j 仍然要自增
		{
			i++;
			j++;
		}
		else
		{
			j = nextval[j];//next数组赋值
		}
	}
	if (j >= len2)
		return i - j;//返回匹配成功的初始下标
	return -1;//此时失败，返回-1
}



int main()
{
	char str1[] = "adsadjdj";
	char str2[] = "djd";
	int pos = 0;//可以决定从主串的任意下标开始匹配
	int k = KMP(str1, str2,0);//返回匹配的下标
	printf("%d", k);
	return 0;
}