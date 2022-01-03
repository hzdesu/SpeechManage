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
	//构造函数
	SpeechManager();
	//显示菜单
	void Show_Menu();
	//初赛选手的容器 12个
	vector<int> v1;
	//复赛选手的容器 6个
	vector<int> v2;
	//决赛选手的容器 3个
	vector<int> v3;
	//存放编号  以及对应的具体选手的容器
	map<int, Speaker> m_Speaker;
	//设置比赛轮数
	int m_Index;
	//初始化属性
	void InitSpeech();
	//初始化创建12名选手
	void CtrateSpeaker();
	//开始比赛
	void StartSpeech();
	//抽签
	void SpeechDraw();
	//比赛
	void SpeechContest();
	//显示比赛结果
	void ShowScore();
	//保存记录
	void SaveRecord();
	//查看往届记录
	void LoadRecord();
	//文件为空的标志
	bool FileIsEmpty;
	//往届记录
	map<int, vector<string>>m_Record;
	//显示往届得分
	void ShowRecord();
	//清空记录
	void ClearRecord();


	//退出系统
	void ExitSystem();
	//析构函数                    
	~SpeechManager();
};