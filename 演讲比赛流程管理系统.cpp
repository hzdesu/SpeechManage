#include<iostream>
using namespace std;
#include"speechManager.h"
#include<ctime>

int main()
{
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	////测试代码
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "编号：" << it->first 
	//		<< "\t姓名：" << it->second.m_Name
	//		<< "\t成绩：" << it->second.m_Score[0] << endl;
	//}

	int choice = 0;
	while (true)
	{
		//显示菜单
		sm.Show_Menu();
		cout << "请输入选项" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:		// 1.开始演讲比赛
			sm.StartSpeech();
			break;
		case 2:		// 2.查看往届记录
			sm.ShowRecord();
			break;
		case 3:		//3.清空比赛记录
			sm.ClearRecord();
			break;
		case 0:		//0.退出比赛程序
			sm.ExitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}



	system("pause");
	return 0;
}