//2021.2.2~2.4

#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

using namespace std;


int main()
{

	workManager wm;		//ʵ���������߶���
	int choice = 0;		//�洢�û���ѡ��
	while (true)
	{
		wm.Show_Menu();
		cout << "����������ѡ�� " << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:		//�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1:		//���ְ��
			wm.Add_Emp();
			break;
		case 2:		//��ʾְ��
			wm.show_Emp();
			break;
		case 3:		//ɾ��ְ��
			wm.delete_Emp();
			break;
		case 4:		//�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5:		//����ְ��
			wm.Find_Emp();
			break;
		case 6:		//����ְ��
			wm.Sort_Emp();
			break;
		case 7:		//����ļ�
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}

	}


	system("pause");
	return 0;
}