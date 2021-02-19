#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<time.h>
#include "Node.h"
#include "Astar.h"
using namespace std;
using namespace cv;

const int mapSize = 50;   // 地图大小
const int imgGridSize = 5;// 显示的图像栅格大小

// 设置障碍物
void defineObstacle(vector<vector<node*>>& roadmap) {
    // 先框住四周
    for (int i = 0; i < mapSize; ++i) {
        roadmap[0][i]->setObstacle();
        roadmap[i][0]->setObstacle();
        roadmap[i][mapSize - 1]->setObstacle();
        roadmap[mapSize - 1][i]->setObstacle();
    }

    // 再定义一个条形快
    for (int i = 1; i < mapSize / 2; ++i) {
        roadmap[mapSize * 2 / 3][i]->setObstacle();
        roadmap[mapSize * 2 / 3 - 1][i]->setObstacle();
        roadmap[mapSize * 1 / 3][mapSize - i]->setObstacle();
        roadmap[mapSize * 1 / 3 - 1][mapSize - i]->setObstacle();
    }
}

// 画出地图
void drawMap(Mat& background, node startNode, node goalNode, vector<vector<node*>> roadmap) {
    // 画出障碍物
    for (int i = 0; i < mapSize; ++i) {
        for (int j = 0; j < mapSize; ++j) {
            if (roadmap[i][j]->isObstacle())
                roadmap[i][j]->drawNode(background, imgGridSize, Scalar(0, 0, 0));
        }
    }

    // 画出起始点和终点
    startNode.drawNode(background, imgGridSize, Scalar(255, 0, 0));//起点为蓝色
    goalNode.drawNode(background, imgGridSize, Scalar(0, 0, 255)); //目标位置为红色
}

int main(int argc, char* argv[]) {
    
    node startNode(40, 10);// 起始点
    node goalNode(10, 40); // 目标点

    vector<vector<node*>> roadmap;// 地图

    // 初始化roadmap
    for (int i = 0; i < mapSize; ++i) {
        vector<node*> tmp;
        for (int j = 0; j < mapSize; ++j) {
            node* tmpNode = new node(i, j);
            tmp.push_back(tmpNode);
        }
        roadmap.push_back(tmp);
    }

    // 添加障碍物
    defineObstacle(roadmap);

    // 打开一个窗口
	namedWindow("aStar", WINDOW_NORMAL);
    
    Mat background(mapSize * imgGridSize,
                   mapSize * imgGridSize,
                   CV_8UC3,//8位无符号char型,3通道
                   cv::Scalar(255, 255, 255));

    // 画出地图
    drawMap(background, startNode, goalNode, roadmap);
    imshow("aStar", background);
    waitKey(5);

	clock_t startTime, endTime;
	startTime = clock();
	Astar astar;
	astar.InitAstar(roadmap);
	astar.GetPath(startNode, goalNode, false, background, imgGridSize);
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	waitKey(0);
    return 0;
}