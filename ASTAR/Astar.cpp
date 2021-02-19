#include "Astar.h"

void Astar::InitAstar(vector<vector<node*>> &_maze){
	maze = _maze;
}

node* Astar::getLeastFpoint(){
	if (!openList.empty()){
		auto resPoint = openList.front();
		for (auto point : openList){
			if (point->getF() < resPoint->getF()) {
				resPoint = point;
			}
		}
		return resPoint;
	}
	return NULL;
}

node* Astar::isInList(const std::list<node *> &list, node* point) const
{
	//判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
	for (auto p : list){
		if (p->getx() == point->getx()  &&  p->gety() == point->gety())
			return p;
	}
	return NULL;
}


bool Astar::isCanreach(node *point, node *target, bool isIgnoreCorner) const //判断某点是否可以用于下一步判断
{
	if (target->getx() < 0 || target->getx() > maze.size() - 1
		|| target->gety() < 0 || target->gety() > maze[0].size() - 1
		|| maze[target->getx()][target->gety()]->isObstacle()
		|| (target->getx() == point->getx() && target->gety() == point->gety())
		|| isInList(closeList, target)) {//如果点超出地图、是障碍物、与当前节点重合、或者在关闭列表中，返回false
		return false;
	}
	else{
		if (abs(point->getx() - target->getx()) + abs(point->gety() - target->gety()) == 1) {//非斜角可以
			return true;
		}
		else{
			//斜对角要判断是否绊住
			if (!maze[point->getx()][target->gety()]->isObstacle() && !maze[target->getx()][point->gety()]->isObstacle()) {
				return true;
			}
			else {
				return isIgnoreCorner;
			}
				
		}
	}
}


vector<node *> Astar::getSurroundPoints(node *point, bool isIgnoreCorner) const{
	std::vector<node *> surroundPoints;
	for (int x = point->getx() - 1; x <= point->getx() + 1; x++) {
		for (int y = point->gety() - 1; y <= point->gety() + 1; y++) {
			if (isCanreach(point, new node(x, y), isIgnoreCorner)) {
				surroundPoints.push_back(new node(x, y));
			}
		}
	}
	return surroundPoints;
}


node* Astar::findPath(node &startPoint, node &endPoint, bool isIgnoreCorner, Mat& background, int imgGridSize)
{
	openList.push_back(new node(startPoint.getx(), startPoint.gety())); //置入起点,拷贝开辟一个节点，内外隔离
	while (!openList.empty()){
		auto curPoint = getLeastFpoint(); //找到F值最小的点
		curPoint->drawNode(background, imgGridSize, Scalar(0, 255, 0), 0);
		imshow("aStar", background);
		waitKey(5);
		openList.remove(curPoint); //从开启列表中删除
		closeList.push_back(curPoint); //放到关闭列表
		//1,找到当前周围八个格中可以通过的格子
		auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
		for (auto &target : surroundPoints){
			//2,对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
			if (!isInList(openList, target)){
				target->setParent(curPoint);
				target->setG(target->calG(curPoint));
				target->setH(target->calH(&endPoint));
				target->setF(target->calF());
				openList.push_back(target);
				/*target->drawNode(background, imgGridSize, Scalar(0, 255, 0), 0);
				imshow("aStar", background);
				waitKey(5);*/
			}
			//3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
			else{
				int tempG = target->calG(curPoint);
				if (tempG < target->getG()){
					target->setParent(curPoint);
					target->setG(tempG);
					target->setF(target->calF());
				}
			}
			node *resPoint = isInList(openList, &endPoint);
			if (resPoint)
				return resPoint; //返回列表里的节点指针，不要用原来传入的endpoint指针，因为发生了深拷贝
		}
	}
	return NULL;
}



std::list<node*> Astar::GetPath(node& startPoint, node& endPoint, bool isIgnoreCorner, Mat& background, int imgGridSize)
{
	node *result = findPath(startPoint, endPoint, isIgnoreCorner, background, imgGridSize);
	std::list<node *> path;
	//返回路径，如果没找到路径，返回空链表
	while (result){
		result->drawNode(background, imgGridSize, Scalar(0, 255, 255), 0);
		imshow("aStar", background);
		waitKey(5);
		path.push_front(result);
		result = result->getParent();
	}
	return path;
}
