#pragma once
#include<iostream>
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#define FILENAME "empFile.txt"
using namespace std;

class workManager
{
public:
	//���캯��
	workManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void ExitSystem();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker** m_EmpArray;

	//���Ա��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա�����ļ������ݣ�
	void init_Emp();

	//��ʾְ��
	void show_Emp();

	//�ж�Ա���Ƿ����,���ڷ���λ�ã������ڷ���-1
	int IsExist(int id);
	int IsExist(string name);

	//ɾ��ְ��
	void delete_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//��������
	~workManager();


};