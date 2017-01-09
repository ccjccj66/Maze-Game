#include "stdafx.h"
#include "PublicResources_Header.h"
#include <vector>

bool InitMazeData(void)
{
	int flagC = 0, flagP = 0;                                                //��ʶ��ʿ�빫���ĵ��Ƿ��Ѿ���ʼ��
	for (int i = 0; i < ARRAY_SIZE; ++i) {                                   //ɨ��ÿһ����
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			if (MAP[i][j] == 'P') {
				CavalierPoint.InsertData(i, j);                              //��ʼ����ʿ��
				flagC = 1;
			}
			if (MAP[i][j] == '#') {
				PrincessPoint.InsertData(i, j);                              //��ʼ��������
				flagP = 1;
			}
		}
	}
	if (flagC*flagP==0) {                                                    //�����ʿ�����������㵱����һ��û�г�ʼ�����
		return false;                                                        //��ʼ�����ɹ�
	}
	return true;
}

bool InitListData(void)
{
	for (int i = 0; i < ARRAY_SIZE; ++i) {                                   //ɨ��ÿһ����
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			if (MAP[i][j] == '0') {                                          //���Ϊ�������ߵĵ�λ
				FeasibleList.InsertData(Point(i, j));                        //������е�
			}
		}
	}
	FeasibleList.ShowList();
	return true;
}

bool InitTreeData(void)
{
	bool noWay = true;
	vector<TreeMaze*> leafs;
	leafs.push_back(&LabyrinthTree);
	while (FeasibleList.getNodeNumber()){
		noWay = true;
		//Ϊ�ײ���������һ������
		for (int i = 0; i < leafs.size(); ++i) {
			Point sonPoint = leafs[i]->GetPoint();
			leafs[i]->SetSonTree(FindSonWay(sonPoint));
		}
		
		vector<TreeMaze*> tempLeafs = leafs;
		leafs.clear();

		for (int i = 0; i < tempLeafs.size(); ++i) {
			for (int j = 0; j < tempLeafs[i]->GetSonNodeNumber(); ++j) {
				leafs.push_back(tempLeafs[i]->GetSonNode(j)->data);
				noWay = false;
			}
		}
		tempLeafs.clear();

		if (FeasibleList.getNodeNumber() == 0 || noWay) {
			return true;
		}
	}
	return true;
}


LinkList *FindSonWay(Point data)
{
	LinkList *sonWay = new LinkList;
	Point up = Point(data.GetX(), data.GetY() - 1);
	Point down = Point(data.GetX(), data.GetY() + 1);
	Point left = Point(data.GetX() - 1, data.GetY());
	Point right = Point(data.GetX() + 1, data.GetY());

	bool flag = false;

	if (FeasibleList.SearchNode(up) != -1) {
		sonWay->InsertData(up);
		FeasibleList.DeleteData(up);
		flag = true;
	}
	if (FeasibleList.SearchNode(down) != -1) {
		sonWay->InsertData(down);
		FeasibleList.DeleteData(down);
		flag = true;
	}
	if (FeasibleList.SearchNode(left) != -1) {
		sonWay->InsertData(left);
		FeasibleList.DeleteData(left);
		flag = true;
	}
	if (FeasibleList.SearchNode(right) != -1) {
		sonWay->InsertData(right);
		FeasibleList.DeleteData(right);
		flag = true;
	}
	if (flag == false) {
		return NULL;
	}else{
		return  sonWay;
	}
}

bool ShowWay(TreeMaze* tree) 
{
	Point princessUp = Point(PrincessPoint.GetX(), PrincessPoint.GetY() - 1);
	Point princessDown = Point(PrincessPoint.GetX(), PrincessPoint.GetY() + 1);
	Point princessLeft = Point(PrincessPoint.GetX() - 1, PrincessPoint.GetY());
	Point princessRight = Point(PrincessPoint.GetX() + 1, PrincessPoint.GetY());

	if (tree->GetSonNodeNumber() == 0) {
		if (tree->GetPoint() == princessUp || tree->GetPoint() == princessDown
			|| tree->GetPoint() == princessLeft || tree->GetPoint() == princessRight) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		for (int i = 0; i < tree->GetSonNodeNumber(); ++i) {
			if (ShowWay(tree->GetSonNode(i)->data)) {
				CString temp;
				temp.Format(_T("<-[%d,%d]"), tree->GetSonNode(i)->data->GetPoint().GetX(), tree->GetSonNode(i)->data->GetPoint().GetY());
				walkWay += temp;
				cout << "<-[" << tree->GetSonNode(i)->data->GetPoint().GetX() << "," << tree->GetSonNode(i)->data->GetPoint().GetY() << "]";
				return true;
			}
		}
	}
	return false;
}

bool DoMaze(void)
{
	if (!InitMazeData()) {
		cout << "This map has problem , please check the map!" << endl;
		exit(-1);
	}
	else {
		cout << "This map init ok!" << endl;
	}
	InitListData();
	LabyrinthTree.InsertData(CavalierPoint);
	InitTreeData();

	CString temp;
	temp.Format(_T("[%d,%d]"), PrincessPoint.GetX(), PrincessPoint.GetY());
	walkWay += temp;
	cout << "[" << PrincessPoint.GetX() << "," << PrincessPoint.GetY() << "]";
	ShowWay(&LabyrinthTree);
	temp.Format(_T("<-[%d,%d]"), CavalierPoint.GetX(), CavalierPoint.GetY());
	walkWay += temp;
	cout << "<-[" << CavalierPoint.GetX() << "," << CavalierPoint.GetY() << "]";
}