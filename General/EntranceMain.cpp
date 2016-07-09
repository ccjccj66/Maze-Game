#include "Header.h"

int main()
{
	Point bishop, gateway;                                                         //�������Ӹ��ŵ�λ��
	if (!InitPoint(&bishop, &gateway)) {                                           //�����Ӹ��ŵ�λ���ҵ�
		printf("ERROR ! Could not find elements !\n");                             //��û�г�ʼ���ɹ�
		exit(-1);                                                                  //���û�г�ʼ���ɹ���ô���޷�������ȥ
	}
	else {
		printf("Initialize the point OK !\n");                                     //��ʼ����ɹ���
	}
	SqStack stepStack;                                                             //����ջ
	if (!stepStack.InitStack()) {                                                  //ջ��ʼ��
		printf("ERROR ! Stack initialization failed !\n");                         //��ʼ��ջʧ����
	}
	else {
		printf("Initialize Stack the OK !\n");                                     //��ʼ��ջ�ɹ�
	}
	if (DisposeKeyWalk(&stepStack, &bishop, &gateway) == false) {                  //Ѱ��·��
		printf("No path can perform !\n");                                         //û��·������
	}
	else{
		printf("We have find the way !\n\n\n");

		printf("================================================================================\n\n");

		ElemType *temp = (ElemType*)malloc(sizeof(ElemType)*stepStack.StackLength());
		int i;
		for (i = 0; !stepStack.StackEmpty(); ++i) {
			stepStack.Pop(&temp[i]);
		}
		printf("[%d,%d]", bishop.X, bishop.Y);
		do {
			i--;
			switch (temp[i])
			{
			case 'W': bishop.Y--; break;                                           //������
			case 'A': bishop.X--; break;                                           //������
			case 'S': bishop.Y++; break;                                           //������
			case 'D': bishop.X++; break;                                           //������
			default:break;
			}
			printf("->[%d,%d]",bishop.X,bishop.Y);
		} while (i);
	}
	printf("\n\n");
	return 0;
}
