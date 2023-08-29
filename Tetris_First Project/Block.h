#pragma once
#include <graphics.h>// �Ȱ�װeasyxͼ�ο�
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
	void rotate();//��ת
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

