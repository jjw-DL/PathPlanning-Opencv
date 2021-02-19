#include "Node.h"

node::node(int _x, int _y, int _G, int _H, int _F) : 
	x(_x), y(_y), G(_G), H(_H), F(_F), obstacle(false), parent(NULL){}

node::~node() {}

int node::getx(){
	return x;
}
int node::gety(){
	return y;
}

int node::calG(node *temp_start) {
	int extraG = (abs(x - temp_start->x) + abs(y - temp_start->y)) == 1 ? kCost1 : kCost2;
	int parentG = parent == NULL ? 0 : parent->G;
	return parentG + extraG;
}

void node::setG(int g) {
	G = g;
}

int node::getG(){
	return G;
}

int node::calH(node* end){
	return (abs(x - end->getx()) + abs(y - end->gety())) * kCost1;
}

void node::setH(int h) {
	H = h;
}

int node::getH() {
	return H;
}

int node::calF() {
	return G + H;
}

void node::setF(int f) {
	F = f;
}

int node::getF() {
	return F;
}

void node::setObstacle() {
	obstacle = true;
}

bool node::isObstacle() {
	return obstacle;
}

void node::setParent(node* backNode) {
	parent = backNode;
}

node* node::getParent() {
	return parent;
}

void node::drawNode(Mat& background, int imgGridSize, const Scalar& color, int shift) {
    rectangle(background,
              Point(x * imgGridSize, y * imgGridSize),
              Point((x + 1) * imgGridSize, (y + 1) * imgGridSize),
              color, shift);
}

