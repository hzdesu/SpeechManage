#include"speechManager.h"


//构造函数
SpeechManager::SpeechManager() 
{
	//初始化属性
	this->InitSpeech();
	//创建选手
	this->CtrateSpeaker();
	//获取往届记录
	this->LoadRecord();

}

//显示菜单
void SpeechManager::Show_Menu()
{
	cout << "*********************************" << endl;
	cout << "****** 欢迎参加演讲比赛    ******" << endl;
	cout << "******   1.开始演讲比赛    ******" << endl;
	cout << "******   2.查看往届记录    ******" << endl;
	cout << "******   3.清空比赛记录    ******" << endl;
	cout << "******   0.退出比赛程序    ******" << endl;
	cout << "*********************************" << endl;

}

//初始化属性
void SpeechManager::InitSpeech()
{
	//容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m_Speaker.clear();
	//初始化比赛轮数
	this->m_Index = 1;
	//初始化记录容器
	this->m_Record.clear();
}

//初始化创建12名选手
void SpeechManager::CtrateSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < size(nameSeed); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//12名选手编号
		this->v1.push_back(i + 10001);
		//把选手编号 以及对应的选手 存放到map容器里
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

//抽签
void  SpeechManager::SpeechDraw()
{
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "--------------" << endl;
	cout << "抽签后演讲排序如下：" << endl;
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

//比赛
void SpeechManager::SpeechContest()
{
	cout << "--------------第" << this->m_Index << "轮比赛开始----------------" << endl;
	multimap<double, int, greater<double>>groupScore;		//临时容器，保存key分数	value选手编号
	int num = 0;	//记录人员数，6个为一组

	vector<int>v_Src;		//比赛的人员容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}


	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = rand() % 401 + 600 / 10.f;	//400~600
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_back();//去除最后一名
		d.pop_front();//去除第一名

		double sum = accumulate(d.begin(), d.end(), 0.0f);	//获取总分
		double avg = sum / (double)d.size();		//获取平均分

		//每个人平均分
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6个人一组，用临时容器存放
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "姓名：" << this->m_Speaker[it->second].m_Name
					<< "分数：" << this->m_Speaker[it->second].m_Score[m_Index - 1] << endl;
			}

			int count = 0;

			//取前三名
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
	cout << "----------第" << this->m_Index << "轮比赛完毕-----------" << endl;
	system("pause");
}

//显示比赛结果
void SpeechManager::ShowScore()
{
	cout << "---------------第" << this->m_Index << "轮晋级选手信息如下：-------------" << endl;
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
		cout << "选手编号" << *it << "选手姓名：" << m_Speaker[*it].m_Name << "得分：" << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->Show_Menu();

}

//保存记录
void SpeechManager::SaveRecord()
{
	ofstream ofs;
	//ios::app 追加模式打开文件夹， 以ios::app打开,如果没有文件，那么生成空文件；如果有文件，那么在文件尾 追加。
	ofs.open("speech.csv", ios::out | ios::app);		//用输出的方式打开文件		--写文件

	//将每个人的数据写入到文件中
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();

	cout << "记录已经保存" << endl;

	//有记录了，文件不为空
	this->FileIsEmpty = false;

}

//开始比赛
void SpeechManager::StartSpeech()
{
	//第一轮比赛
	//1、抽签
	SpeechDraw();
	//2、比赛
	SpeechContest();
	//3、显示晋级结果
	ShowScore();

	this->m_Index++;
	//第二轮比赛
	//1、抽签
	SpeechDraw();
	//2、比赛
	SpeechContest();
	//3、显示最终结果
	ShowScore();
	//4、保存分数      
	SaveRecord();

	//重置比赛
	//初始化属性
	this->InitSpeech();
	//创建选手
	this->CtrateSpeaker();
	//获取往届记录
	this->LoadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

//查看往届记录
void SpeechManager::LoadRecord()
{
	ifstream ifs("speech.csv", ios::in);	//输入流对象  读取文件

	if (!ifs.is_open())
	{
		this->FileIsEmpty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->FileIsEmpty = false;
	ifs.putback(ch);		//读取的单个字符放回去
	
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);		//从0开始查找','
			if (pos == -1)
			{
				break;	//找不到brerak返回
			}
			string tmp = data.substr(start, pos - start);	//找到了，进行分割	参数1 起始位置，参数2 截取位置
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

//显示往届得分
void SpeechManager::ShowRecord()
{
	if (this->FileIsEmpty)
	{
		cout << "文件不存在，或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届  " <<
				"冠军编号：" << this->m_Record[i][0] << "  得分：" << this->m_Record[i][1] << " "
				"亚军编号：" << this->m_Record[i][2] << "  得分：" << this->m_Record[i][3] << " "
				"季军编号：" << this->m_Record[i][4] << "  得分：" << this->m_Record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::ClearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;
	
	if (select == 1)
	{
		//打开模式		ios::trunc	如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		
		//初始化属性
		this->InitSpeech();
		//创建选手
		this->CtrateSpeaker();
		//获取往届记录
		this->LoadRecord();

		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

//退出系统
void SpeechManager::ExitSystem()
{
	cout << "退出系统" << endl;
	system("pause");
	exit(0);
}

//析构函数 
SpeechManager::~SpeechManager()
{

}