#ifndef _NODE_H
#define _NODE_H

#include <vector>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

const int kCost1 = 10; //直移一格消耗
const int kCost2 = 14; //斜移一格消耗

// 用来存储节点
class node {
public:
	node(int _x = 0, int _y = 0, int _G = 0, int _H = 0, int _F = 0);
    ~node();
	int getx();
	int gety();

	int calG(node *temp_start);
	void setG(int g);
	int getG();

	int calH(node* end);
	void setH(int h);
	int getH();

	int calF();
	void setF(int f);
	int getF();

	void setObstacle();
	bool isObstacle();
	void setParent(node* backNode);
	node* getParent();
	void drawNode(Mat& background, int imgGridSize, const Scalar& color, int shift = -1);
private:
    int x, y;       // 坐标
	int  G, H, F;	//F=G+H
    bool obstacle;   // 是否是障碍物
    node* parent; // 前驱节点
};

#endif
