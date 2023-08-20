#include "Tetris.h"


Tetris::Tetris(int rows, int cols, int left, int top, int blocksize)
{

}

void Tetris::init()
{
	delay = 30;
}

void Tetris::KeyEvent()
{
	//need to finish
	update = true;
}

void Tetris::updateWindows()
{

}

int Tetris::getDelay()
{
	return 0;
}

void Tetris::drop()
{
}

void Tetris::clearline()
{
}


void Tetris::play()
{
	init();
	int timer = 0;
	while (1)
	{
		//接受用户的输入
		KeyEvent();
		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();
			update = true;
		}
		if (update)
		{
			update = false;
			//更新画面
			updateWindows();
			//更新数据
			clearline();
		}
	}
}