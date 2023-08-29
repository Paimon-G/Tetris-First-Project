#pragma once
#include <graphics.h>
#include <vector>
#include"Block.h"
using namespace std;
class Tetris
{
public:
	//构造函数
	Tetris(int rows, int cols, int left, int top, int blocksize);
	void init();//初始化
	void play();//开始
private:
	void KeyEvent();
	void updateWindows();
	int getDelay();//返回调用上一次函数的间隔时间
	void drop();
	void clearline();
	void moveLeftRight(int offset);
	void rotate();
	void drawScore();// 绘制当前分数
	void checkover();
	void savescore();
	void displayover();
private:
	int delay;
	bool update;//是否更新
	// 0是空白，即没有方块
	// 是几就表示是哪一种方块
	vector<vector<int>> map;
	int rows, cols;
	int LeftMargin, topMargin;
	int blockSize;
	IMAGE imgBg;
	Block* curBlock;
	Block* nextBlock;// 下一个方块
	Block backBlock; // 当前方块中用来备份的方块
	int score;
	int highestscore;
	int level;
	int linecount; // 一共消了多少行
	bool gameover;
	IMAGE imgover;
	IMAGE imgwin;
};