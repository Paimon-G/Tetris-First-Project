#pragma once
#include <graphics.h>// 先安装easyx图形库
#include <vector>
using namespace std;
struct Point
{
	int row, col;
};
class Block
{
public:
	Block();
	void drop();
	void moveLeftRight(int offset);
	void rotate();//旋转
	void draw(int LeftMargin,int TopMargin);
	static IMAGE** getImages();
	Block& operator=(const Block& other);
	bool blockinMap(const vector<vector<int>>& Map);
	void solidfy(vector<vector<int>>& Map);
	int getBlockType();
private:
	int blockType;
	Point smallBlocks[4];
	IMAGE *img;
	static IMAGE* imgs[7];
	static int size;
};

