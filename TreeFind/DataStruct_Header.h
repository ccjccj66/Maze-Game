#pragma once
#include <iostream>
using namespace std;

class Point;
class LNode;
class LinkList;
class TreeMaze;

using ElemType = TreeMaze;                                                   //���޸�

class Point                                                                  //�����Թ��е�ÿ��������ݽṹ
{
private:
	int x;                                                                   //������������Ϊ0-9��x����ֵ
	int y;                                                                   //���ϵ�������Ϊ0-9��y����ֵ
public:
	Point(int tempX = 0, int tempY = 0) :x(tempX), y(tempY) {}               //����ֱ��Ϊ���ʼ����ֵ��Ҳ����Ĭ��Ϊ0��ֵ
	~Point() {}                                                              //���������޲���
	void InsertData(int, int);                                               //�����ݸ�������
	int GetX(void);                                                          //��Ϊ�����ӿڣ��ṩxֵ�ķ��ط���
	int GetY(void);                                                          //��Ϊ�����ӿڣ��ṩyֵ�ķ��ط���
	void ClearData(void);                                                    //������ݽṹ���е�����
	friend bool operator ==(Point,Point);
};

class LNode                                                                  //��ʾ�����е�ÿһ���ڵ�
{
public:
	ElemType *data;                                                          //ÿһ���ڵ��������
	LNode *next;                                                             //ָ���������һ���ڵ�
	LNode();
};

class LinkList                                                               //��������ݽṹ��1.������ 2.���Ľ���У�
{
private:
	LNode *head;                                                             //�����ͷ
	LNode *tail;                                                             //����ı�β
	int nodeNumber;                                                          //�ڵ�ĸ���
public:
	LinkList() { head = tail = NULL; nodeNumber = 0; }                       //��ʼ����ͷ��β������
	~LinkList() {}
	int getNodeNumber();                                                     //��ȡ���е�ĸ���
	void InsertData(Point);                                                  //�������в���һ���ڵ㣨��Ϊû������������ֻ����һ���㣩
	bool DeleteData(void);                                                   //ɾ�������е�һ���ڵ�
	bool DeleteData(Point);                                                  //ɾ�������е�ָ��һ���ڵ�
	int SearchNode(Point);
	LNode GetListNode(void);                                                 //����ͷָ��ָ��ĵ�һ���ڵ�����
	LNode *GetListNode(int);                                                  //����ָ��λ���ϵĽڵ�
	void ShowList(void);                                                     //��ʾ���������еĽڵ��Point��ֵ
	void ClearList(void);                                                    //����������е�����
};

class TreeMaze                                                               //һ�����Ĵ洢�ṹ
{
private:
	Point data;                                                              //���еĽڵ���Դ
	LinkList *sonTree;                                                       //��ǰ�����ӽڵ��ǣ�ΪNULL��ʾ�˽ڵ�ΪҶ��
public:
	TreeMaze() { sonTree = NULL; }                                                            //Ĭ�ϵĹ��캯��
	TreeMaze(Point tempPoint) { data = tempPoint; sonTree = NULL; }
	~TreeMaze() {}
	
	/*���е����༸������*/
	void InsertData(Point);                                                  //�����в������ݲ���
	Point GetPoint(void);                                                    //��ȡ����ǰ���ݵ�
	int GetDepth(void);                                                      //��ȡ�������
	LNode *GetSonNode(int);
	void SetSonTree(LinkList*);
	int GetSonNodeNumber(void);
};