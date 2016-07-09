#include "Header.h"
bool InitPoint(Point *bishop, Point *gateway)                                  //��ʼ�����Ӹ��ſڵ�λ��
{
	int flagBishop = 0, flagGateway = 0;                                       //������û���ҵ���ı�־
	for (int i = 0; i < ARRAY_SIZE; ++i) {                                     //�Ե�ͼ�����е��ɨ�����
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			switch (Map[i][j])                                                 //�жϵ���ȷ��Ҫִ��ʲô����
			{
			case 'P':
			case 'p': bishop->X = j; bishop->Y = i; flagBishop++; break;       //�������ӵ�λ�ò����ñ�־
			case '#': gateway->X = j; gateway->Y = i; flagGateway++; break;    //�����ŵ�λ�ò����ñ�־
			default:break;
			}
			if (flagBishop == 1 && flagGateway == 1) {                         //�����־���ɹ��ˣ���ô�������سɹ�
				return OK;
			}
		}
	}
	return ERROR;                                                              //���������־��û��ȫ��������ϣ���ô������ʼ����Ч
}
char PointWalk(SqStack *stepStack, Point *standPerson)                         //�����˺�һ���Ĳ���
{
	char step;                                                                 //����������ǰ��һ��ǰ�������еķ���
	if (!stepStack->Pop(&step)) {                                              //�����ոս��еķ���
		printf("Stack ERROR! \n");                                             //ջ����ջ����ֻ��һ�����������ջ��û����ֵ
		step = 'B';                                                            //����B
	}
	/*=================================================*/
	printf("pop %c\n", step);
	/*=================================================*/
	switch (step)                                                              //���ǰ���в���Ļ����Ͱ�������ķ�ʽȥ����
	{
	case 'W': standPerson->Y++; break;                                         //ǰһ����������
	case 'A': standPerson->X++; break;                                         //ǰһ����������
	case 'S': standPerson->Y--; break;                                         //ǰһ����������
	case 'D': standPerson->X--; break;                                         //ǰһ����������
	default:break;
	}
	return step;                                                               //�����B����ջ�Ѿ�Ϊ��
}
char PointWalk(SqStack *stepStack, Point *standPerson, char step)              //����ǰ��һ���Ĳ���
{
	step = JudgeStep(stepStack, standPerson, step);                            //�Լ���Ҫ�ߵĲ��������жϣ���߷��ػ����WASDB���������·��
	switch (step)                                                              //������һ���������ߵĲ��ӣ����ǿ��Զ�������ж��Բ���
	{
	case 'W': standPerson->Y--; break;                                         //������
	case 'A': standPerson->X--; break;                                         //������
	case 'S': standPerson->Y++; break;                                         //������
	case 'D': standPerson->X++; break;                                         //������
	case 'B': step = PointWalk(stepStack, standPerson);                        //�����ʱҪ�����ˣ�ִ�к��˲��Ӳ���
		if (step == 'B') {
			return 'B';
		}
		/*���ʱ��Ӧ�ð���ǰ���߹��ķ��򿴿���һ��������ʲô*/
		return step;
		/*�����⣡������*/


	default: printf("Judge step ERROR! \n"); exit(-1); break;                  //���������������������ж�ʧ��
	}
	/*=================================================*/
	printf("push %c\n",step);
	/*=================================================*/
	stepStack->Push(step);                                                     //�������ߵ�һ������ջ��
	return 'N';
}
char JudgeStep(SqStack *stepStack, Point *standPerson, char step)
{
	char stepTemp[7] = "NAWDSB";                                               //������·�����˳��
	char stepSave;
	stepStack->GetTop(&stepSave);
	//�������Ǹ���֮ǰ�߹��Ĳ��ӣ����ж���һ��Ҫ�ߵ���ʲô���ӣ�������
	//��������һ���µĲ��ӣ�step=��N��
	//BΪ��ǰ���п����ߵĲ����Ѿ������ˣ���Ҫ�˺�һ����
	//=============================================================
	//Ҫ֪����ԭ���ߵ���һ������ô�ߵģ�Ȼ��Ͳ��ܴ��Ǹ��ط���ȥ,Ҳ���ǲ��ܵ��ڶ�ջ��������Ǹ�
	//judge��Ҫ����ȷ�����Ե��ж�
	for (int i = 0; i < 5; ++i) {                                              //��ǰ����ɨ��
		//1.ȷ����������ǿ����ߵ�
		//2.ȷ����������Ǹղ��������෴����
		//3.ȷ�����������N�Ĵ�����
		//4.ȷ���������������˳���
		if (step == stepTemp[i]) {                                             //�ҵ��ղ��ߵķ���
			step = stepTemp[i + 1];                                            //����ԭ�����޷����ߣ����ȵ���һ������
			if (JudgeStepBack(stepSave, step) ||                               //���·�������ԭ�����෴
				JudgeStepDoable(*standPerson, step)) {                         //����ǰ���·�Ƿ����赲
				continue;                                                      //��������������������·��ͨ��������һ������
			}
			else {                                                             //����˷����ǿ��еģ����˳�
				break;
			}
		}
	}
	if (step == 'N') {                                                         //���ֵĴ����жϣ�һ�����ǲ����ܵ�
		printf("Judge ERRPR! \n");
		exit(-1);                                                              //�ٴγ���N���������ֹ
	}
	return step;                                                               //���ؿ������ߵķ���
}
bool JudgeStepBack(char stepBefore, char stepAfter)
{
	if (stepBefore == 'W'&&stepAfter == 'S' ||                                 //�������෴����
		stepBefore == 'S'&&stepAfter == 'W' ||                                 //�������෴����
		stepBefore == 'A'&&stepAfter == 'D' ||                                 //�������෴����
		stepBefore == 'D'&&stepAfter == 'A') {                                 //�������෴����
		return true;
	}
	else{
		return false;
	}
}
bool JudgeStepDoable(Point standPerson, char step)                             //standPerson������ֵ�����Ե��ж������ֵ��������ԭ����û��Ӱ��
{
	switch (step)                                                              //��ֵ����
	{
	case 'W': standPerson.Y--; break;
	case 'A': standPerson.X--; break;
	case 'S': standPerson.Y++; break;
	case 'D': standPerson.X++; break;
	}
	if (Map[standPerson.Y][standPerson.X] == '1') {                            //����ǽ��
		return true;
	}
	else {
		return false;
	}
}
bool DisposeKeyWalk(SqStack *stepStack, Point *bishop, Point *gateway)         //��·��ѭ��
{
	Point bishopWalk = *bishop;
	char step = 'N';
	while (true) {
		if (step == 'B'&&stepStack->StackEmpty()) {
			return false;
		}
		//PointWalk��ʹ�õ�����һ���߹���·�ӡ�   Ȼ�󽫱����ߵ�·�ӷ��ؼ�¼��Ȼ��������һ�ε�ʹ��
		step = PointWalk(stepStack, &bishopWalk, step);
		printf("[%d,%d]\n",bishopWalk.X,bishopWalk.Y);
		stepStack->ShowStack();
		if (bishopWalk.X == gateway->X&&bishopWalk.Y == gateway->Y) {
			break;
		}
	}
	return true;
}