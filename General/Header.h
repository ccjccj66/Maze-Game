#pragma once
//#include <cctype>
#include <stdio.h>                                                             //����֧�ֻ���IO����
#include <stdlib.h>                                                            //����֧���ڴ�������
#include <string.h>                                                            //����֧���ַ�������
#define OK 1                                                                   //����Stack��bool�෵��
#define ERROR 0                                                                //����Stack��bool�෵��
#define MAX_SIZE 80                                                            //�궨stack�����洢ֵ
#define STACK_INT_SIZE 10                                                      //����Stack�ĳ�ʼ��С
#define STACKINCREMENT 5                                                       //����Stack����չ��С
#define ARRAY_SIZE 10                                                          //���õ�ͼ�Ĵ�С
typedef char ElemType;                                                         //�궨Stack�д洢���ݵ�����

const char Map[ARRAY_SIZE][ARRAY_SIZE] = {                                     //���õ�ͼ�е�����
	{ '1','1','1','1','1','1','1','1','1','1' },
	{ '1','0','1','1','0','0','0','1','0','#' },
	{ '1','0','1','1','0','1','1','1','0','1' },
	{ '1','0','0','0','0','1','1','1','0','1' },
	{ '1','0','1','1','1','0','0','0','0','1' },
	{ '1','0','0','P','1','0','1','1','0','1' },
	{ '1','0','1','0','0','0','1','1','0','1' },
	{ '1','0','1','1','1','0','1','1','0','1' },
	{ '1','1','0','0','0','0','0','0','0','1' },
	{ '1','1','1','1','1','1','1','1','1','1' },
};

class SqStack                                                                  //Stack��Ķ���
{
private:
	ElemType *base;                                                            //ջ��λ��ֵ
	ElemType *top;                                                             //����ջ��λ��ֵ
	int stacksize;                                                             //��ʾջ��ǰ�������ݵĸ���
public:
	int InitStack(void);                                                       //��ʼ��ջ
	int ClearStack(void);                                                      //���ջ
	int StackEmpty(void);                                                      //�ж�ջ�Ƿ�Ϊ��
	int StackLength(void);                                                     //����ջ��Ԫ�ظ���
	int Push(ElemType e);                                                      //ѹ������
	int Pop(ElemType *e);                                                      //��������
	int GetTop(ElemType *e);                                                   //����ջ������
	void ShowStack(void);                                                      //���ջ�����е�Ԫ��
};

typedef struct Point                                                           //��ṹ�Ķ���
{
	int X = 0;                                                                 //�������ֵ
	int Y = 0;                                                                 //�������ֵ
}Point;

bool InitPoint(Point *, Point *);                                              //��ʼ�����Ӹ��ſڵ�λ��
char PointWalk(SqStack *, Point *);                                            //�����˺�һ���Ĳ���
char PointWalk(SqStack *, Point *,char);                                       //����ǰ��һ���Ĳ���
char JudgeStep(SqStack *, Point *, char);
bool JudgeStepBack(char , char);
bool JudgeStepDoable(Point , char );
bool DisposeKeyWalk(SqStack *, Point *, Point *);