#pragma once
#include <graphics.h>
#include <vector>
#include"Block.h"
using namespace std;
class Tetris
{
public:
	//���캯��
	Tetris(int rows, int cols, int left, int top, int blocksize);
	void init();//��ʼ��
	void play();//��ʼ
private:
	void KeyEvent();
	void updateWindows();
	int getDelay();//���ص�����һ�κ����ļ��ʱ��
	void drop();
	void clearline();
	void moveLeftRight(int offset);
	void rotate();
	void drawScore();// ���Ƶ�ǰ����
	void checkover();
	void savescore();
	void displayover();
private:
	int delay;
	bool update;//�Ƿ����
	// 0�ǿհף���û�з���
	// �Ǽ��ͱ�ʾ����һ�ַ���
	vector<vector<int>> map;
	int rows, cols;
	int LeftMargin, topMargin;
	int blockSize;
	IMAGE imgBg;
	Block* curBlock;
	Block* nextBlock;// ��һ������
	Block backBlock; // ��ǰ�������������ݵķ���
	int score;
	int highestscore;
	int level;
	int linecount; // һ�����˶�����
	bool gameover;
	IMAGE imgover;
	IMAGE imgwin;
};