/*
* 设计两个类
* block and Teris
* 设计接口，对外部的调用
* 启动
* 
*/


/*
* 待解决的bug
* 1.方块固定后不显示
*/

#include"Tetris.h"
#include<iostream>
int main()
{
	Tetris game(20, 10, 263, 133, 36);
	game.play();
	return 0;
}