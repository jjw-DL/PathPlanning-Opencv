#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include "Node.h"
class Astar{
public:
	void InitAstar(vector<vector<node*>> &_maze);
	std::list<node*> GetPath(node& startPoint, node& endPoint, bool isIgnoreCorner, Mat& background, int imgGridSize);
private:
	node *findPath(node &startPoint, node &endPoint, bool isIgnoreCorner, Mat& background, int imgGridSize);
	vector<node *> getSurroundPoints(node *point, bool isIgnoreCorner) const;
	bool isCanreach(node *point, node *target, bool isIgnoreCorner) const; //判断某点是否可以用于下一步判断
	node *isInList(const std::list<node *> &list, node *point) const; //判断开启/关闭列表中是否包含某点
	node *getLeastFpoint(); //从开启列表中返回F值最小的节点
private:
	vector<vector<node*>> maze;
	std::list<node *> openList;  //开启列表
	std::list<node *> closeList; //关闭列表
};

#endif