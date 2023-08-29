#include "Block.h"
#include <stdlib.h>

IMAGE* Block::imgs[7] = { NULL,};
int Block::size = 36;
int blocks[7][4] =
{
	1,3,5,7,// I
	2,4,5,7,// Z
	3,5,4,7,// T
	2,3,5,7,// L
	3,5,7,6,// J
	2,3,4,5,// 田
};
Block::Block()
{
	if (imgs[0] == NULL)
	{
		// 切割图片
		IMAGE imgTmp;// 定义临时的图片变量
		loadimage(&imgTmp, "res/tiles.png");
		SetWorkingImage(&imgTmp);
		for (int i = 0; i < 7; i++)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i],i*size,0,size,size);
		}
		SetWorkingImage();// 恢复工作区

	}
	//随机生成一种方块 
	blockType = rand() % 7 + 1;
	//初始化smallblocks
	for (int i = 0; i < 4; i++)
	{
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;
		smallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];

}

void Block::drop()
{
	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].row++;
	}
}

void Block::moveLeftRight(int offset)
{
	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].col += offset;
	}
}

void Block::rotate()
{
	Point p = smallBlocks[1];
	for (int i = 0; i < 4; i++)
	{
		Point temp = smallBlocks[i];
		smallBlocks[i].col = p.col - temp.row + p.row;
		smallBlocks[i].row = p.row + temp.col - p.col;
	}
}

void Block::draw(int LeftMargin, int TopMargin)
{
	for (int i = 0; i < 4; i++)
	{
		int x = LeftMargin+ smallBlocks[i].col * size;
		int y = TopMargin + smallBlocks[i].row * size;
		putimage(x, y, img);
	}
}

IMAGE** Block::getImages()
{
	return imgs;
}

Block& Block::operator=(const Block& other)
{
	if (this == &other)
	{
		return *this;
	}
	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++)
	{
		this->smallBlocks[i] = other.smallBlocks[i];
	}
	return *this;
}

bool Block::blockinMap(const vector<vector<int>>& Map)
{
	int rows = Map.size();
	int cols = Map[0].size();
	for (int i = 0; i < 4; i++)
	{
		if (smallBlocks[i].col < 0 
			||
			smallBlocks[i].col >= cols 
			||
			smallBlocks[i].row < 0 
			||
			smallBlocks[i].row >= rows 
			|| 
			Map[smallBlocks[i].row][smallBlocks[i].col])
		{
			return false;
		}
	}
	return true;
}

void Block::solidfy(vector<vector<int>>& Map)
{
	for (int i = 0; i < 4; i++)
	{
		// 固化对应的位置
		Map[smallBlocks[i].row][smallBlocks[i].col] = blockType;
	}
}

int Block::getBlockType()
{
	return blockType;
}
