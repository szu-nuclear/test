//����
#pragma once
#include<iostream>
#include"worker.h"

using namespace std;

class Manager :public Worker
{
public:
	//���캯��
	Manager(int id, string name, int dId);

	//��ʾ������Ϣ
	void showInfo();


	//��ȡ��λ����
	string getDeptName();

};

