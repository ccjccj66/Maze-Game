#include "PublicResources_Header.h"

LinkList FeasibleList;                                                       //��ʾ�������ߵĵ���
TreeMaze LabyrinthTree;                                                      //����·����
Point CavalierPoint;                                                         //��ʿ���ڵ�λ��
Point PrincessPoint;                                                         //�������ڵ�λ��

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
	InitTreeData();
	return 0;
}