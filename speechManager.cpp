#include"speechManager.h"


//���캯��
SpeechManager::SpeechManager() 
{
	//��ʼ������
	this->InitSpeech();
	//����ѡ��
	this->CtrateSpeaker();
	//��ȡ�����¼
	this->LoadRecord();

}

//��ʾ�˵�
void SpeechManager::Show_Menu()
{
	cout << "*********************************" << endl;
	cout << "****** ��ӭ�μ��ݽ�����    ******" << endl;
	cout << "******   1.��ʼ�ݽ�����    ******" << endl;
	cout << "******   2.�鿴�����¼    ******" << endl;
	cout << "******   3.��ձ�����¼    ******" << endl;
	cout << "******   0.�˳���������    ******" << endl;
	cout << "*********************************" << endl;

}

//��ʼ������
void SpeechManager::InitSpeech()
{
	//������֤Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m_Speaker.clear();
	//��ʼ����������
	this->m_Index = 1;
	//��ʼ����¼����
	this->m_Record.clear();
}

//��ʼ������12��ѡ��
void SpeechManager::CtrateSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < size(nameSeed); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//12��ѡ�ֱ��
		this->v1.push_back(i + 10001);
		//��ѡ�ֱ�� �Լ���Ӧ��ѡ�� ��ŵ�map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

//��ǩ
void  SpeechManager::SpeechDraw()
{
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "--------------" << endl;
	cout << "��ǩ���ݽ��������£�" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "============" << endl;
	system("pause");
	cout << endl;
}

//����
void SpeechManager::SpeechContest()
{
	cout << "--------------��" << this->m_Index << "�ֱ�����ʼ----------------" << endl;
	multimap<double, int, greater<double>>groupScore;		//��ʱ����������key����	valueѡ�ֱ��
	int num = 0;	//��¼��Ա����6��Ϊһ��

	vector<int>v_Src;		//��������Ա����
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}


	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = rand() % 401 + 600 / 10.f;	//400~600
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_back();//ȥ�����һ��
		d.pop_front();//ȥ����һ��

		double sum = accumulate(d.begin(), d.end(), 0.0f);	//��ȡ�ܷ�
		double avg = sum / (double)d.size();		//��ȡƽ����

		//ÿ����ƽ����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6����һ�飬����ʱ�������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "������" << this->m_Speaker[it->second].m_Name
					<< "������" << this->m_Speaker[it->second].m_Score[m_Index - 1] << endl;
			}

			int count = 0;

			//ȡǰ����
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					v3.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "----------��" << this->m_Index << "�ֱ������-----------" << endl;
	system("pause");
}

//��ʾ�������
void SpeechManager::ShowScore()
{
	cout << "---------------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�-------------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = v3;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ��" << *it << "ѡ��������" << m_Speaker[*it].m_Name << "�÷֣�" << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->Show_Menu();

}

//�����¼
void SpeechManager::SaveRecord()
{
	ofstream ofs;
	//ios::app ׷��ģʽ���ļ��У� ��ios::app��,���û���ļ�����ô���ɿ��ļ���������ļ�����ô���ļ�β ׷�ӡ�
	ofs.open("speech.csv", ios::out | ios::app);		//������ķ�ʽ���ļ�		--д�ļ�

	//��ÿ���˵�����д�뵽�ļ���
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//�ر��ļ�
	ofs.close();

	cout << "��¼�Ѿ�����" << endl;

	//�м�¼�ˣ��ļ���Ϊ��
	this->FileIsEmpty = false;

}

//��ʼ����
void SpeechManager::StartSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	SpeechDraw();
	//2������
	SpeechContest();
	//3����ʾ�������
	ShowScore();

	this->m_Index++;
	//�ڶ��ֱ���
	//1����ǩ
	SpeechDraw();
	//2������
	SpeechContest();
	//3����ʾ���ս��
	ShowScore();
	//4���������      
	SaveRecord();

	//���ñ���
	//��ʼ������
	this->InitSpeech();
	//����ѡ��
	this->CtrateSpeaker();
	//��ȡ�����¼
	this->LoadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

//�鿴�����¼
void SpeechManager::LoadRecord()
{
	ifstream ifs("speech.csv", ios::in);	//����������  ��ȡ�ļ�

	if (!ifs.is_open())
	{
		this->FileIsEmpty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->FileIsEmpty = false;
	ifs.putback(ch);		//��ȡ�ĵ����ַ��Ż�ȥ
	
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);		//��0��ʼ����','
			if (pos == -1)
			{
				break;	//�Ҳ���brerak����
			}
			string tmp = data.substr(start, pos - start);	//�ҵ��ˣ����зָ�	����1 ��ʼλ�ã�����2 ��ȡλ��
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

//��ʾ����÷�
void SpeechManager::ShowRecord()
{
	if (this->FileIsEmpty)
	{
		cout << "�ļ������ڣ����¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "��  " <<
				"�ھ���ţ�" << this->m_Record[i][0] << "  �÷֣�" << this->m_Record[i][1] << " "
				"�Ǿ���ţ�" << this->m_Record[i][2] << "  �÷֣�" << this->m_Record[i][3] << " "
				"������ţ�" << this->m_Record[i][4] << "  �÷֣�" << this->m_Record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::ClearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;
	
	if (select == 1)
	{
		//��ģʽ		ios::trunc	�������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		
		//��ʼ������
		this->InitSpeech();
		//����ѡ��
		this->CtrateSpeaker();
		//��ȡ�����¼
		this->LoadRecord();

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

//�˳�ϵͳ
void SpeechManager::ExitSystem()
{
	cout << "�˳�ϵͳ" << endl;
	system("pause");
	exit(0);
}

//�������� 
SpeechManager::~SpeechManager()
{

}