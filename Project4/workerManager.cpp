#include"workerManager.h"

//构造函数
workManager::workManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//1、第一次使用，文件未创建
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2、文件存在，但数据被用户清空
	char ch;
	ifs >> ch;
	if (ifs.eof())		//End of flie
	{
		//cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3、文件存在，并且保存职工的所有数据
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//数组初始化
	this->init_Emp();

}

//展示菜单
void workManager::Show_Menu()
{
	cout << "************************************************" << endl;
	cout << "************* 欢迎使用职工管理系统 *************" << endl;
	cout << "**************** 0.退出管理系统 ****************" << endl;
	cout << "**************** 1.增加职工信息 ****************" << endl;
	cout << "**************** 2.显示职工信息 ****************" << endl;
	cout << "**************** 3.删除离职员工 ****************" << endl;
	cout << "**************** 4.修改职工信息 ****************" << endl;
	cout << "**************** 5.查找职工信息 ****************" << endl;
	cout << "**************** 6.按照编号排序 ****************" << endl;
	cout << "**************** 7.清空所有文档 ****************" << endl;
	cout << "************************************************" << endl;
}

//退出系统
void workManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加职工
void workManager::Add_Emp()
{
	cout << "请输入添加职工数量：" << endl;

	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)//添加
	{
		//计算添加新空间的大小
		int newSize = addNum + this->m_EmpNum;

		//创建新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下的数据拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
			
			//flag等于0表示该id可以存入
			int flag = 1;
			do
			{
				cin >> id;
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]->m_Id == id)
					{
						cout << "该编号已存在，请重新输入：" << endl;
						break;
					}
					flag = 0;
				}

			} while (flag&&this->m_FileIsEmpty ==false );//如果文件为空for循环无法执行，且可以直接赋值

			
			

			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;
			cout << "请选择该职工的岗位：\n1、普通职工、\n2、经理\n3、老板\n";
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//将创建的职工指针保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;

		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "输入数据有误" << endl;
	}
	system("pause");
	system("cls");
}

//保存文件
void workManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;	
	}
	ofs.close();
}

//统计文件的人数
int workManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

//初始化员工（文件有数据）
void workManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else
		{
			worker=new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工
void workManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		this->m_EmpArray[i]->showInfo();
	}
	system("pause");
	system("cls");
}

//判断员工是否存在
int workManager::IsExist(int id)
{
	for (int i=0;i<this->m_EmpNum;i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			return i ;
		}
	}
	return -1;
}

int workManager::IsExist(string name)
{
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Name== name)
		{
			return i ;
		}
	}
	return -1;
}

//删除职工
void workManager::delete_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;		
	}
	else 
	{
		cout << "1、按编号删除\n2、按姓名删除" << endl;
		int choice;

		cin >> choice;
		if (choice == 1 || choice == 2)
		{
			if (choice == 1)//按编号删除
			{
				cout << "请输入编号：" << endl;
				int id;
				cin >> id;

				if (this->IsExist(id)==-1)
				{
					cout << "查无此人" << endl;					
				}

				else
				{
					int tmp = this->IsExist(id);
					for(int i = tmp;i < this->m_EmpNum-1; i++)
					{
						this->m_EmpArray[i] = this->m_EmpArray[i + 1];
					}
					this->m_EmpNum--;
					//更新到文件
					this->save();
					cout << "删除成功" << endl;

				}
			}
			else//按名字删除
			{
				cout << "请输入名字：" << endl;
				string name;
				cin >> name;

				if (this->IsExist(name) == -1)
				{
					cout << "查无此人" << endl;
				}

				else
				{
					int tmp = this->IsExist(name);
					for (int i = tmp; i < this->m_EmpNum - 1; i++)
					{
						this->m_EmpArray[i] = this->m_EmpArray[i + 1];
					}
					this->m_EmpNum--;
					//更新到文件
					this->save();
					cout << "删除成功" << endl;

				}
			}
		}
		else 
		{
			cout << "输入有误" << endl;
		}
	}
	
	system("pause");
	system("cls");

}

//修改职工
void workManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入编号：" << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "查无此人" << endl;
		}
		else
		{					
			//释放原先的职工
			delete this->m_EmpArray[index];
					
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << "号职工，请输入新职工号:" << endl;
			
			//flag等于0表示该id可以存入
			int flag = 1;
			do
			{
				cin >> newId;
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]->m_Id == newId)
					{
						cout << "该编号已存在，请重新输入：" << endl;
						break;
					}
					flag = 0;
				}

			} while (flag && this->m_FileIsEmpty == false);//如果文件为空for循环无法执行，且可以直接赋值
			



			cout << "请输入新的名字" << endl;
			cin >> newName;

			cout << "请输入新的部门编号" << endl;
			cout << "1、普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.董事长" << endl;
			cin >> dSelect;

			Worker* temp_wm = NULL;
			switch (dSelect)
			{
				case 1:
				{
					temp_wm = new Employee(newId, newName, 1);
				}
				case 2:
				{
					temp_wm = new Manager(newId, newName, 2);
				}
				case 3:
				{
					temp_wm = new Boss(newId, newName, 3);
				}
			}	
			this->m_EmpArray[index] = temp_wm;
			//更新到文件
			this->save();
			cout << "修改成功" << endl;
		}
	}

	system("pause");
	system("cls");
}

//查找职工
void workManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或不存在" << endl;
	}
	else
	{
		cout << "1、按编号查找\n2、按姓名查找" << endl;
		int choice;
		cin >> choice;

		if (choice == 1)//按编号查找
		{
			cout << "请输入编号：" << endl;
			int s_id;
			cin >> s_id;
			if (this->IsExist(s_id) == -1)
			{
				cout << "员工不存在" << endl;
			}
			else
			{
				int index = this->IsExist(s_id);
				cout << index << endl;
				this->m_EmpArray[index]->showInfo();
				cout << "222" << endl;
			}
		}

		else//按姓名查找
		{
			cout << "请输入姓名：" << endl;
			string name;
			cin >> name;

			if (this->IsExist(name) == -1)
			{
				cout << "员工不存在" << endl;
			}

			else
			{
				int index = this->IsExist(name);
				this->m_EmpArray[index]->showInfo();
			}
		}


	}
	system("pause");
	system("cls");
}

//排序职工
void workManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或不存在" << endl;
	}
	else
	{
		cout << "请选择排序的方式：" << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		//选择排序算法
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
						{
							minOrMax = j;
						}
				}
				else
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}

			}

			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功" << endl;
		this->save();
		this->show_Emp();
	}
}

//清空文件 选择排序
void workManager::Clean_File()
{
	cout << "确定清空?" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		//删除堆区数据
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");

}

//析构函数
workManager::~workManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}