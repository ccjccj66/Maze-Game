#include "DataStruct_Header.h"

void Point::InsertData(int dataX, int dataY) 
{
	x = dataX;                                                               //Ϊ��X��ʼ��
	y = dataY;                                                               //Ϊ��Y��ʼ��
}

int Point::GetX(void)
{
	return x;                                                                //����X����ֵ
}

int Point::GetY(void)
{
	return y;                                                                //����Y����ֵ
}

void Point::ClearData(void)
{
	x = 0;                                                                   //�����X������
	y = 0;                                                                   //�����Y������
}

bool operator==(Point point_A, Point point_B)
{
	if (point_A.GetX() == point_B.GetX() && point_A.GetY() == point_B.GetY()) {
		return true;
	}
	return false;
}


LNode::LNode()                                                               //�½�����ڵ��ʱ��Ϊ���������������ռ� 
{
	//data = (TreeMaze*)malloc(sizeof(TreeMaze));                            //ΪLNode��ʼ���ռ�
}

int LinkList::getNodeNumber()                                                //��ȡ���е�ĸ���
{
	return nodeNumber;
}

void LinkList::InsertData(Point data)
{
	if (nodeNumber == 0) {                                                   //���ڵ���Ϊ0ʱ
		head = tail = (LNode*)malloc(sizeof(LNode));                         //��ʱ�½�һ���ڵ㣬ͷ�ڵ�β�ڵ㶼�Ǵ˽ڵ�
		head->data = (ElemType*)malloc(sizeof(ElemType));                    //ΪLNode��ʼ���ռ�
		head->data->InsertData(data);                                        //��ֵ���ڵ�����ݲ���
		head->data->SetSonTree(NULL);
		head->next = NULL;                                                   //�˽ڵ����һ�ڵ�Ϊ��
	}
	else {                                                                   //��ʱ�����ж���ڵ�
		LNode *temp = (LNode*)malloc(sizeof(LNode));                         //�½��ڵ�
		temp->data = (ElemType*)malloc(sizeof(ElemType));                    //ΪLNode��ʼ���ռ�
		temp->data->InsertData(data);                                        //�������
		temp->data->SetSonTree(NULL);
		temp->next = NULL;                                                   //�������β��Ϊ��
		tail->next = temp;                                                   //��β�ڵ����½��ڵ�����
		tail = temp;                                                         //��ʱ�½ڵ㼰Ϊ�µ�β�ڵ�
	}
	nodeNumber++;                                                            //�ڵ�������
}

bool LinkList::DeleteData(void)
{
	if (nodeNumber == 0) {                                                   //��������û�нڵ��ʱ��
		return false;                                                        //�޷��س���
	}
	else {
		LNode *temp = head;                                                  //��ͷ�ڵ��λ�ñ�������
		head = head->next;                                                   //����ͷ�ڵ�Ϊ��һ���ڵ�λ��
		free(temp);                                                          //�ͷ�ԭ��ͷ�ڵ��е�����ֵ
		if (nodeNumber == 1) {                                               //����ڵ���ԭ����1�ģ���ô����û�нڵ��ˣ���β�ڵ���Ȼ�ڿ�λ��
			tail = NULL;                                                     //β�ڵ���������
		}
	}
	nodeNumber--;                                                            //�ڵ�����С
	cout << "Delete LNode OK!" << endl;
	return true;
}

bool LinkList::DeleteData(Point data)
{
	if (nodeNumber == 0) {                                                   //��������û�нڵ��ʱ��
		return false;                                                        //�޷��س���
	}
	else {
		LNode *temp = head;                                                  //��ͷ�ڵ��λ�ñ�������
		LNode *before = temp;                                                //����Ҫɾ����ǰһ����
		while (temp) {                                                       //ѭ����ѰҪɾ���ĵ�
			Point pTemp = temp->data->GetPoint();                            //��ȡ����
			if (pTemp.GetX() == data.GetX() &&                               //�Ա�����
				pTemp.GetY() == data.GetY()) {
				break;
			}
			before = temp;                                                   //��ʱ�����㼴�����ɾ�����ǰһ����
			temp = temp->next;                                               //���������
		}
		if (temp == NULL) {                                                  //�˵㲻����
			return false;
		}
		before->next = temp->next;                                           //ɾ��temp��
		if (temp == head) {                                                  //���ɾ������ͷ��
			head = head->next;                                               //ԭ����ɾ������û���κ����ã�Ҫ����ɾ��
		}
		else if (temp == tail) {                                             //���ɾ������β��
			tail = before;                                                   //ǰһ�������β��
			before->next = NULL;                                             //ǰһ�������һ���ڵ����˿�
		}
		free(temp);                                                          //�ͷ�ԭ��ͷ�ڵ��е�����ֵ
		if (nodeNumber == 1) {                                               //����ڵ���ԭ����1�ģ���ô����û�нڵ��ˣ���β�ڵ���Ȼ�ڿ�λ��
			tail = NULL;                                                     //β�ڵ���������
		}
	}
	nodeNumber--;                                                            //�ڵ�����С
	cout << "Delete LNode OK!" << endl;
	return true;
}

int LinkList::SearchNode(Point data)
{
	int index = 0;
	LNode *temp = this->head;
	while (temp){
		if (temp->data->GetPoint() == data) {
			return index;
		}
		temp = temp->next;
		++index;
	}
	return -1;
}

LNode LinkList::GetListNode(void)
{
	return *head;                                                            //����ͷ�ڵ�ָ�������
}

LNode *LinkList::GetListNode(int index)
{
	if (index < 0 || index > nodeNumber) {
		cout << "Error : Get list node over !" << endl;
		return NULL;
	}
	else {
		LNode *temp = this->head;
		for (int i = 0; i < nodeNumber; ++i) {
			if (i == index) {
				return temp;
			}
			temp = temp->next;
		}
	}
}

void LinkList::ShowList(void)
{
	LNode *temp = this->head;
	while (temp) {
		Point pTemp = temp->data->GetPoint();
		temp = temp->next;
		cout << "[" << pTemp.GetX() << "," << pTemp.GetY() << "]" << "->";
	}
	cout << "NULL" << endl;
}

void LinkList::ClearList(void)
{
	while (head != NULL) {                                                   //ֱ����ͷΪ��Ϊֹ
		LNode *temp = head;                                                  //�����ɾ���ڵ�Ĳ���һ��
		head = head->next;
		free(temp);
	}
}

void TreeMaze::InsertData(Point data)
{
	this->data.InsertData(data.GetX(), data.GetY());                         //Ϊ���������ݲ���
}

Point TreeMaze::GetPoint(void)
{
	return Point(data.GetX(), data.GetY());                                  //�������ݲ���
}

int TreeMaze::GetDepth(void)
{
	if (this->sonTree == NULL) {
		return 1;
	}
	else {
		int sumDepth = 0;
		for (int i = 0; i < this->sonTree->getNodeNumber(); ++i) {
			LNode *tempNode = this->sonTree->GetListNode(i);
			sumDepth += tempNode->data->GetDepth();
		}
		return sumDepth;
	}
	return 0;
}

LNode *TreeMaze::GetSonNode(int index)
{
	return sonTree->GetListNode(index);
}

void TreeMaze::SetSonTree(LinkList *sonTree)
{
	this->sonTree = sonTree;
}

int TreeMaze::GetSonNodeNumber(void)
{
	if (this->sonTree == NULL) {
		return 0;
	}else{
		return sonTree->getNodeNumber();
	}
}