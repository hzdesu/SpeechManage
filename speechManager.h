#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<random>
#include<deque>
#include<numeric>
#include"speaker.h"
using namespace std;

class SpeechManager
{
public:
	//���캯��
	SpeechManager();
	//��ʾ�˵�
	void Show_Menu();
	//����ѡ�ֵ����� 12��
	vector<int> v1;
	//����ѡ�ֵ����� 6��
	vector<int> v2;
	//����ѡ�ֵ����� 3��
	vector<int> v3;
	//��ű��  �Լ���Ӧ�ľ���ѡ�ֵ�����
	map<int, Speaker> m_Speaker;
	//���ñ�������
	int m_Index;
	//��ʼ������
	void InitSpeech();
	//��ʼ������12��ѡ��
	void CtrateSpeaker();
	//��ʼ����
	void StartSpeech();
	//��ǩ
	void SpeechDraw();
	//����
	void SpeechContest();
	//��ʾ�������
	void ShowScore();
	//�����¼
	void SaveRecord();
	//�鿴�����¼
	void LoadRecord();
	//�ļ�Ϊ�յı�־
	bool FileIsEmpty;
	//�����¼
	map<int, vector<string>>m_Record;
	//��ʾ����÷�
	void ShowRecord();
	//��ռ�¼
	void ClearRecord();


	//�˳�ϵͳ
	void ExitSystem();
	//��������                    
	~SpeechManager();
};