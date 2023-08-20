/*
* 设计两个类
* block and Teris
* 设计接口，对外部的调用
* 启动
* 
*/

#include"Tetris.h"
int main()
{
	Tetris game(20, 10, 163, 133, 36);
	game.play();
	return 0;
}