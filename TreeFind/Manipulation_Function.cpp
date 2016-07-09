#include "PublicResources_Header.h"

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
	//Test delete
	/*
	{
		FeasibleList.DeleteData();
		FeasibleList.DeleteData(Point(1, 1));
		FeasibleList.DeleteData(Point(1, 2));
		FeasibleList.DeleteData(Point(5, 6));
		FeasibleList.DeleteData(Point(8, 7));
		FeasibleList.DeleteData(Point(8, 8));
	}
	*/
	return true;
}

bool InitTreeData(void)
{
	while (FeasibleList.getNodeNumber()) {

	}
}


