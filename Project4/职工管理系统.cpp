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

	workManager wm;		//实例化管理者对象
	int choice = 0;		//存储用户的选择
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入您的选择： " << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:		//退出系统
			wm.ExitSystem();
			break;
		case 1:		//添加职工
			wm.Add_Emp();
			break;
		case 2:		//显示职工
			wm.show_Emp();
			break;
		case 3:		//删除职工
			wm.delete_Emp();
			break;
		case 4:		//修改职工
			wm.Mod_Emp();
			break;
		case 5:		//查找职工
			wm.Find_Emp();
			break;
		case 6:		//排序职工
			wm.Sort_Emp();
			break;
		case 7:		//清空文件
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