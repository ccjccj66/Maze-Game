#pragma once
#include "DataStruct_Header.h"

extern int ARRAY_SIZE;
extern char **MAP;

extern LinkList FeasibleList;                                                       //��ʾ�������ߵĵ���
extern TreeMaze LabyrinthTree;                                                      //����·����
extern Point CavalierPoint;                                                         //��ʿ���ڵ�λ��
extern Point PrincessPoint;                                                         //�������ڵ�λ��
extern TreeMaze FindPrincess;
extern CString walkWay;

bool InitMazeData(void);                                                     //��ʼ����Ҫ���������ڵ�
bool InitListData(void);                                                     //��ʼ�������������е���ֵ
bool InitTreeData(void);                                                     //��ʼ�����е�ֵ
LinkList *FindSonWay(Point);
bool ShowWay(TreeMaze*);
bool DoMaze(void);


/*
##########
#  #   # 0
#  #   # #
#    ##  #
# ###    #
#  P#    #
# #   #  #
# ### ## #
##       #
##########

 '#''#''#''#''#''#''#''#''#''#' 
 '#'' '' ''#'' '' '' ''#'' ''Q' 
 '#'' '' ''#'' '' '' ''#'' ''#' 
 '#'' '' '' '' ''#''#'' '' ''#' 
 '#'' ''#''#''#'' '' '' '' ''#' 
 '#'' '' ''P''#'' '' '' '' ''#' 
 '#'' ''#'' '' '' ''#'' '' ''#' 
 '#'' ''#''#''#'' ''#''#'' ''#' 
 '#''#'' '' '' '' '' '' '' ''#' 
 '#''#''#''#''#''#''#''#''#''#' 

*/