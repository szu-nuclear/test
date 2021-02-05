#include"workerManager.h"

//���캯��
workManager::workManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//1����һ��ʹ�ã��ļ�δ����
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ����ڣ������ݱ��û����
	char ch;
	ifs >> ch;
	if (ifs.eof())		//End of flie
	{
		//cout << "�ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3���ļ����ڣ����ұ���ְ������������
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;
	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//�����ʼ��
	this->init_Emp();

}

//չʾ�˵�
void workManager::Show_Menu()
{
	cout << "************************************************" << endl;
	cout << "************* ��ӭʹ��ְ������ϵͳ *************" << endl;
	cout << "**************** 0.�˳�����ϵͳ ****************" << endl;
	cout << "**************** 1.����ְ����Ϣ ****************" << endl;
	cout << "**************** 2.��ʾְ����Ϣ ****************" << endl;
	cout << "**************** 3.ɾ����ְԱ�� ****************" << endl;
	cout << "**************** 4.�޸�ְ����Ϣ ****************" << endl;
	cout << "**************** 5.����ְ����Ϣ ****************" << endl;
	cout << "**************** 6.���ձ������ ****************" << endl;
	cout << "**************** 7.��������ĵ� ****************" << endl;
	cout << "************************************************" << endl;
}

//�˳�ϵͳ
void workManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//���ְ��
void workManager::Add_Emp()
{
	cout << "���������ְ��������" << endl;

	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)//���
	{
		//��������¿ռ�Ĵ�С
		int newSize = addNum + this->m_EmpNum;

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ��µ����ݿ������¿ռ���
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

			cout << "������� " << i + 1 << " ����ְ����ţ�" << endl;
			
			//flag����0��ʾ��id���Դ���
			int flag = 1;
			do
			{
				cin >> id;
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]->m_Id == id)
					{
						cout << "�ñ���Ѵ��ڣ����������룺" << endl;
						break;
					}
					flag = 0;
				}

			} while (flag&&this->m_FileIsEmpty ==false );//����ļ�Ϊ��forѭ���޷�ִ�У��ҿ���ֱ�Ӹ�ֵ

			
			

			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ��\n1����ְͨ����\n2������\n3���ϰ�\n";
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

			//��������ְ��ָ�뱣�浽������
			newSpace[this->m_EmpNum + i] = worker;

		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ��
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "������������" << endl;
	}
	system("pause");
	system("cls");
}

//�����ļ�
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

//ͳ���ļ�������
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

//��ʼ��Ա�����ļ������ݣ�
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

//��ʾְ��
void workManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		this->m_EmpArray[i]->showInfo();
	}
	system("pause");
	system("cls");
}

//�ж�Ա���Ƿ����
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

//ɾ��ְ��
void workManager::delete_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;		
	}
	else 
	{
		cout << "1�������ɾ��\n2��������ɾ��" << endl;
		int choice;

		cin >> choice;
		if (choice == 1 || choice == 2)
		{
			if (choice == 1)//�����ɾ��
			{
				cout << "�������ţ�" << endl;
				int id;
				cin >> id;

				if (this->IsExist(id)==-1)
				{
					cout << "���޴���" << endl;					
				}

				else
				{
					int tmp = this->IsExist(id);
					for(int i = tmp;i < this->m_EmpNum-1; i++)
					{
						this->m_EmpArray[i] = this->m_EmpArray[i + 1];
					}
					this->m_EmpNum--;
					//���µ��ļ�
					this->save();
					cout << "ɾ���ɹ�" << endl;

				}
			}
			else//������ɾ��
			{
				cout << "���������֣�" << endl;
				string name;
				cin >> name;

				if (this->IsExist(name) == -1)
				{
					cout << "���޴���" << endl;
				}

				else
				{
					int tmp = this->IsExist(name);
					for (int i = tmp; i < this->m_EmpNum - 1; i++)
					{
						this->m_EmpArray[i] = this->m_EmpArray[i + 1];
					}
					this->m_EmpNum--;
					//���µ��ļ�
					this->save();
					cout << "ɾ���ɹ�" << endl;

				}
			}
		}
		else 
		{
			cout << "��������" << endl;
		}
	}
	
	system("pause");
	system("cls");

}

//�޸�ְ��
void workManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "�������ţ�" << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "���޴���" << endl;
		}
		else
		{					
			//�ͷ�ԭ�ȵ�ְ��
			delete this->m_EmpArray[index];
					
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ְ������������ְ����:" << endl;
			
			//flag����0��ʾ��id���Դ���
			int flag = 1;
			do
			{
				cin >> newId;
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]->m_Id == newId)
					{
						cout << "�ñ���Ѵ��ڣ����������룺" << endl;
						break;
					}
					flag = 0;
				}

			} while (flag && this->m_FileIsEmpty == false);//����ļ�Ϊ��forѭ���޷�ִ�У��ҿ���ֱ�Ӹ�ֵ
			



			cout << "�������µ�����" << endl;
			cin >> newName;

			cout << "�������µĲ��ű��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.���³�" << endl;
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
			//���µ��ļ�
			this->save();
			cout << "�޸ĳɹ�" << endl;
		}
	}

	system("pause");
	system("cls");
}

//����ְ��
void workManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
	}
	else
	{
		cout << "1������Ų���\n2������������" << endl;
		int choice;
		cin >> choice;

		if (choice == 1)//����Ų���
		{
			cout << "�������ţ�" << endl;
			int s_id;
			cin >> s_id;
			if (this->IsExist(s_id) == -1)
			{
				cout << "Ա��������" << endl;
			}
			else
			{
				int index = this->IsExist(s_id);
				cout << index << endl;
				this->m_EmpArray[index]->showInfo();
				cout << "222" << endl;
			}
		}

		else//����������
		{
			cout << "������������" << endl;
			string name;
			cin >> name;

			if (this->IsExist(name) == -1)
			{
				cout << "Ա��������" << endl;
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

//����ְ��
void workManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
	}
	else
	{
		cout << "��ѡ������ķ�ʽ��" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;

		//ѡ�������㷨
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
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
		cout << "����ɹ�" << endl;
		this->save();
		this->show_Emp();
	}
}

//����ļ� ѡ������
void workManager::Clean_File()
{
	cout << "ȷ�����?" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		//ɾ����������
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
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");

}

//��������
workManager::~workManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}