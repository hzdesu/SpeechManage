#include<iostream>
using namespace std;
#include"speechManager.h"
#include<ctime>

int main()
{
	srand((unsigned int)time(NULL));

	SpeechManager sm;
	////���Դ���
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "��ţ�" << it->first 
	//		<< "\t������" << it->second.m_Name
	//		<< "\t�ɼ���" << it->second.m_Score[0] << endl;
	//}

	int choice = 0;
	while (true)
	{
		//��ʾ�˵�
		sm.Show_Menu();
		cout << "������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:		// 1.��ʼ�ݽ�����
			sm.StartSpeech();
			break;
		case 2:		// 2.�鿴�����¼
			sm.ShowRecord();
			break;
		case 3:		//3.��ձ�����¼
			sm.ClearRecord();
			break;
		case 0:		//0.�˳���������
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