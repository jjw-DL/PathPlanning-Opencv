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

const int mapSize = 50;   // ��ͼ��С
const int imgGridSize = 5;// ��ʾ��ͼ��դ���С

// �����ϰ���
void defineObstacle(vector<vector<node*>>& roadmap) {
    // �ȿ�ס����
    for (int i = 0; i < mapSize; ++i) {
        roadmap[0][i]->setObstacle();
        roadmap[i][0]->setObstacle();
        roadmap[i][mapSize - 1]->setObstacle();
        roadmap[mapSize - 1][i]->setObstacle();
    }

    // �ٶ���һ�����ο�
    for (int i = 1; i < mapSize / 2; ++i) {
        roadmap[mapSize * 2 / 3][i]->setObstacle();
        roadmap[mapSize * 2 / 3 - 1][i]->setObstacle();
        roadmap[mapSize * 1 / 3][mapSize - i]->setObstacle();
        roadmap[mapSize * 1 / 3 - 1][mapSize - i]->setObstacle();
    }
}

// ������ͼ
void drawMap(Mat& background, node startNode, node goalNode, vector<vector<node*>> roadmap) {
    // �����ϰ���
    for (int i = 0; i < mapSize; ++i) {
        for (int j = 0; j < mapSize; ++j) {
            if (roadmap[i][j]->isObstacle())
                roadmap[i][j]->drawNode(background, imgGridSize, Scalar(0, 0, 0));
        }
    }

    // ������ʼ����յ�
    startNode.drawNode(background, imgGridSize, Scalar(255, 0, 0));//���Ϊ��ɫ
    goalNode.drawNode(background, imgGridSize, Scalar(0, 0, 255)); //Ŀ��λ��Ϊ��ɫ
}

int main(int argc, char* argv[]) {
    
    node startNode(40, 10);// ��ʼ��
    node goalNode(10, 40); // Ŀ���

    vector<vector<node*>> roadmap;// ��ͼ

    // ��ʼ��roadmap
    for (int i = 0; i < mapSize; ++i) {
        vector<node*> tmp;
        for (int j = 0; j < mapSize; ++j) {
            node* tmpNode = new node(i, j);
            tmp.push_back(tmpNode);
        }
        roadmap.push_back(tmp);
    }

    // ����ϰ���
    defineObstacle(roadmap);

    // ��һ������
	namedWindow("aStar", WINDOW_NORMAL);
    
    Mat background(mapSize * imgGridSize,
                   mapSize * imgGridSize,
                   CV_8UC3,//8λ�޷���char��,3ͨ��
                   cv::Scalar(255, 255, 255));

    // ������ͼ
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