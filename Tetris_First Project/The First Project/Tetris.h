#pragma once
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
private:
	int delay;
	bool update;//�Ƿ����
};

