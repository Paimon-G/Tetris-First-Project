#include "Tetris.h"
#include "Block.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <mmsystem.h>
#include <fstream>
#include <iostream>
#pragma comment(lib,"winmm.lib")
#define MAX_LEVEL 5
const int SPEED_NORMAL[MAX_LEVEL] = { 500,300,150,100,80 };

Tetris::Tetris(int rows, int cols, int left, int top, int blocksize)
{
	this->rows = rows;
	this->cols = cols;
	this->LeftMargin = left;
	this->topMargin = top;
	// std::cout << LeftMargin << " " << topMargin << endl;
	for (int i = 0; i < rows; i++)
	{
		vector<int> mapRow;
		for (int j = 0; j < cols; j++)
		{
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}
void Tetris::init()
{
	delay = SPEED_NORMAL[0];
	//�����������
	srand(time(NULL));
	// ��������
	initgraph(938, 896);
	// ���ر���ͼƬ
	loadimage(&imgBg, "res/bg2.png");
	loadimage(&imgwin, "res/win.png");
	loadimage(&imgover, "res/over.png");
	// ��ʼ������
	char data[20][10];
	for (int i = 0 ; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = 0;
		}
	}
	score = 0;
	level = 1;
	linecount = 0;

	// ��ʼ�����ô洢����߷�
	ifstream file("score.txt");
	if (!file.is_open())
	{
		cout<<"score.txt"<<"��ʧ��"<<"\n";
	}
	else
	{
		file>>highestscore;
	}
	file.close();
	gameover = false;
}

void Tetris::KeyEvent()
{
	unsigned char ch; // -128,127
	bool rotateFlag = false;
	int dx = 0;
	if (_kbhit())
	{
		ch=_getch();
		// ������·�������᷵�������ַ�
		// �ϣ�224 72 �£�224 80 ��224 75 �ң�224 77
		if (ch == 224)
		{
			ch = _getch();
			switch (ch)
			{
			case 72: rotateFlag = true;break;// ��ת����
			case 80: delay = SPEED_NORMAL[4]; break;
			case 75: dx = -1; break;
			case 77: dx = 1; break;
			default: break;
			}
		}
	}
	if (rotateFlag)
	{
		// ������ת����
		rotate();
		update = true;
	}
	if (dx != 0)
	{
		// �����ƶ�
		moveLeftRight(dx);
		update = true;
	}
}

void Tetris::updateWindows()
{
	putimage(0, 0, &imgBg);// ����һ��ͼƬ
	IMAGE** imgs = Block::getImages();
	BeginBatchDraw();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == 0)
				continue;
			int x = j * blockSize + LeftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y,imgs[map[i][j]-1]);
		}
	}
	//Block block;
	//block.draw(LeftMargin, topMargin);
	curBlock->draw(LeftMargin, topMargin);
	nextBlock->draw(689, 150);
	drawScore();
	EndBatchDraw();
}

int Tetris::getDelay()
{
	static unsigned long long LastTime = 0;
	unsigned long long currentTime=GetTickCount();
	if (LastTime == 0)
	{
		LastTime = currentTime;
		return 0;
	}
	else
	{
		int ret = currentTime - LastTime;
		LastTime = currentTime;
		return ret;
	}
	return 0;
}

void Tetris::drop()
{
	backBlock = *curBlock;
	curBlock->drop();
	// �½������У��Ѿ������ˣ�
	if (!curBlock->blockinMap(map))
	{
		// �������̻�
		backBlock.solidfy(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
		// ����ǲ��ǽ���
		
	}
	delay = SPEED_NORMAL[level - 1];
}

void Tetris::clearline()
{
	int lines = 0;
	int k = rows - 1; // �洢����
	for (int i = rows - 1; i > 0; i--)
	{
		// ����i��
		int cnt = 0;
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j])
				cnt++;
			map[k][j] = map[i][j]; //һ��ɨ��һ��洢
		}
		if (cnt < cols) // ��������
		{
			k--;
		}
		else // ����ʱ��
		{
			lines++;
		}
	}
	if (lines > 0)
	{
		// ����÷֣�һ�ζ����е÷�Խ��
		int addscore[5] = { 10,30,60,80 };
		score += addscore[lines - 1];
		mciSendString("play res/xiachu1.mp3", 0, 0, 0);
		update = true;

		// ����ؿ���ÿһ�ٷ�Ϊһ������
		level = (score + 99) / 100;
		if (level > MAX_LEVEL)
		{
			gameover = true;
		}
		linecount += lines;
	}
}

void Tetris::moveLeftRight(int offset)
{
	backBlock = *curBlock;
	curBlock->moveLeftRight(offset);
	if (!curBlock->blockinMap(map))
	{
		*curBlock = backBlock;  
	}
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7)
		return;
	backBlock = *curBlock;
	curBlock->rotate();
	if (!curBlock->blockinMap(map))
	{
		*curBlock = backBlock;
	}
}

void Tetris::drawScore()
{
	char scoreText[32];
	// ���Ʒ���
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);
	setcolor(RGB(180, 180, 180));
	LOGFONT f;
	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY;
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Consolas"));
	gettextstyle(&f);
	setbkmode(TRANSPARENT);
	outtextxy(670, 727, scoreText);
	// ������������
	sprintf_s(scoreText, sizeof(scoreText), "%d", linecount);
	gettextstyle(&f);
	int xPos = 224 - f.lfWidth * strlen(scoreText);
	outtextxy(xPos, 816, scoreText);
	// ���Ƶ�ǰ�Ĺؿ���
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(224 - 30, 727, scoreText);
	// ������߷�
	sprintf_s(scoreText, sizeof(scoreText), "%d", highestscore);
	outtextxy(670, 817, scoreText);
}

void Tetris::checkover()
{
	gameover = (curBlock->blockinMap(map)==false);
}

void Tetris::savescore()
{
	if (score > highestscore)
	{
		highestscore = score;
		ofstream file("score.txt");
		file << highestscore;
		file.close();
	}
}

void Tetris::displayover()
{
	if (level <= MAX_LEVEL)
	{
		putimage(262, 361, &imgover);
	}
	else
	{
		putimage(262, 361, &imgwin);
	}
}

void Tetris::play()
{
	init();
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;
	int timer = 0;
	while (1)
	{
		//�����û�������
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
			//���»���
			updateWindows();
			//��������
			clearline();
		}
		if (gameover)
		{
			savescore();
			// ���½���
			displayover();
			system("puase");
			init(); // �ؿ�
		}
	}
}