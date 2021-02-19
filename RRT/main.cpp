#include <iostream>
#include <vector>
#include <time.h>
#include "rrt.h"
using namespace std;

int main(int argc, char* argv[]) {
    // �ϰ���,ǰ��������ʾԲ������,���һ������ʾ�뾶
    vector<vector<float>> obstacleList{
        {7, 5, 1},
        {5, 6, 2},
        {5, 8, 2},
        {5, 10, 2},
        {9, 5, 2},
        {11, 5, 2}
    };

    // ��ʼ���Ŀ���
    node* startNode = new node(2.0, 2.0);
    node* goalNode = new node(14.0, 9.0);
	clock_t startTime, endTime;
	startTime = clock();
    RRT rrt(startNode, goalNode, obstacleList, 0.5, 5);
    rrt.planning();
	endTime = clock();
	cout << "Total Time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	waitKey(0);
    return 0;
}
