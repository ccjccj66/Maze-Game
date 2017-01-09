#include "PublicResources_Header.h"

LinkList FeasibleList;                                                       //��ʾ�������ߵĵ���
TreeMaze LabyrinthTree;                                                      //����·����
Point CavalierPoint;                                                         //��ʿ���ڵ�λ��
Point PrincessPoint;                                                         //�������ڵ�λ��
TreeMaze FindPrincess;                                                       //�ҵ������ķ���

int main()
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

	cout << "[" << PrincessPoint.GetX() << "," << PrincessPoint.GetY() << "]";
	ShowWay(&LabyrinthTree);
	cout << "<-[" << CavalierPoint.GetX() << "," << CavalierPoint.GetY() << "]";
	return 0;
}