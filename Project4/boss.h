//���³�
#pragma once
#include<iostream>
#include"worker.h"

using namespace std;

class Boss :public Worker
{
public:
	//���캯��
	Boss(int id, string name, int dId);

	//��ʾ������Ϣ
	void showInfo();


	//��ȡ��λ����
	string getDeptName();

};
