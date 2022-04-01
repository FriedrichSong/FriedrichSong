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
/////////////�������㷨


void getNext(const char *s,int *next,const int len)//const��ǿ����׳��
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


int KMP(const char* s1, const char* s2, int pos)//KMP��Ҫ�������±겻�ص�������Ч�ʸ���
{
	assert(s1 && s2);//����ȷ���������ǿ�ָ��
	int len1 = strlen(s1);//��������
	int len2 = strlen(s2);//ƥ�䴮����
	if (len1 == 0 || len2 == 0)
		return -1;//����һ��������Ϊ0��˹���û��ʵ�ֵ�����
	if (pos < 0 || pos >= len1)
		return -1;//��������±�Խ�磬�򴫲�������
	int* next = (int*)malloc(sizeof(int) * len2);//����һ��next����
	getNext(s1,next,len2);
	int* nextval = (int*)malloc(sizeof(int) * len2);//�Ż�next
	getNextval(s1,next,len2,nextval);
	int i = pos; int j = 0;
	while (i < len1 && j < len2)//ѭ�����޶ȣ����ᳬ�������ַ�������һ���ĳ���
	{
		if (j == -1 || s1[i] == s2[j])//���ƥ�䴮���ַ�ƥ�䲻�ɹ������᷵��jֵ-1����ʱi j ��ȻҪ����
		{
			i++;
			j++;
		}
		else
		{
			j = nextval[j];//next���鸳ֵ
		}
	}
	if (j >= len2)
		return i - j;//����ƥ��ɹ��ĳ�ʼ�±�
	return -1;//��ʱʧ�ܣ�����-1
}



int main()
{
	char str1[] = "adsadjdj";
	char str2[] = "djd";
	int pos = 0;//���Ծ����������������±꿪ʼƥ��
	int k = KMP(str1, str2,0);//����ƥ����±�
	printf("%d", k);
	return 0;
}