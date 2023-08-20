#pragma once
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
private:
	int delay;
	bool update;//是否更新
};

