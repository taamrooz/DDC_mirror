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
	uint32_t id;
	int width;
	int height;
	int xV;
	int yV;
	Node(Point, uint32_t, int, int, int, int);
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
	~QuadTree();

	void insert(Node*);
	void divide(Node*, Point*);
	void divideNode(Node*);
	//Node* search(Point);
	bool in_boundary(Node*);
	std::vector<std::tuple<Point, Point>> get_bounds();
	std::vector<std::tuple<Node*, Node*>> get_collisions();
};