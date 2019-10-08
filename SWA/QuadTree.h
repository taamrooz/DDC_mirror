#pragma once
#include <vector>

struct Point
{
	int x;
	int y;
	Point(int, int);
};

// The objects that we want stored in the quadtree 
struct Node
{
	Point position;
	int radius;
	int id;
	Node(Point, int, int);
};

class QuadTree {
private:
	Point topLeft;
	Point botRight;

	// Contains array of nodes
	Node* nodes[4];
	int capacity = 4;

	// Children of this tree 
	QuadTree* topLeftTree;
	QuadTree* topRightTree;
	QuadTree* botLeftTree;
	QuadTree* botRightTree;
public:
	QuadTree(Point, Point);

	void insert(Node*);
	void divide(Node*);
	//Node* search(Point);
	bool in_boundary(Point);
	std::vector<std::tuple<Point, Point>> get_bounds();
};