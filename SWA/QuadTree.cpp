#include "QuadTree.h";
#include <vector>
#include <tuple>

Point::Point(int _x, int _y) {
	x = _x;
	y = _y;
}

Node::Node(Point _position, int _id, int _radius) : position(_position), id(_id), radius(_radius) {

}

QuadTree::QuadTree(Point topL, Point botR) : 
    topLeftTree(nullptr), topRightTree(nullptr), botLeftTree(nullptr), botRightTree(nullptr),
	topLeft(topL), botRight(botR) {
}

QuadTree::~QuadTree() {
	delete topLeftTree;
	delete topRightTree;
	delete botLeftTree;
	delete botRightTree;
}

void QuadTree::insert(Node* node) {
	if (!node) {
		return;
	}

	if (!in_boundary(node->position)) {
		return;
	}

	// Add
	bool added = false;
	for (int i = 0; i < capacity; ++i) {
		if (!nodes[i]) {
			nodes[i] = node;
			added = true;
			break;
		}
	}

	if (!added) {
		if (!topLeftTree && !topRightTree && !botLeftTree && !botRightTree) {
			// subdivide all nodes
			for (int i = 0; i < capacity; ++i) {
				divide(nodes[i]);
			}
		}

		// subdivde node
		divide(node);
	}
}

void QuadTree::divide(Node* node) {
	if ((topLeft.x + botRight.x) / 2 >= node->position.x)
	{
		// Indicates topLeftTree 
		if ((topLeft.y + botRight.y) / 2 >= node->position.y)
		{
			if (!topLeftTree)
			{
				topLeftTree = new QuadTree(
					Point{ topLeft.x, topLeft.y },
					Point{ (topLeft.x + botRight.x) / 2,
					(topLeft.y + botRight.y) / 2 });
			}
			topLeftTree->insert(node);
		}

		// Indicates botLeftTree 
		else
		{
			if (!botLeftTree)
			{
				botLeftTree = new QuadTree(
					Point{ topLeft.x,
					(topLeft.y + botRight.y) / 2 },
					Point{ (topLeft.x + botRight.x) / 2,
						botRight.y });
			}
			botLeftTree->insert(node);
		}
	}
	else
	{
		// Indicates topRightTree 
		if ((topLeft.y + botRight.y) / 2 >= node->position.y)
		{
			if (!topRightTree) 
			{
				topRightTree = new QuadTree(
					Point{ (topLeft.x + botRight.x) / 2,
						topLeft.y },
					Point{ botRight.x,
					(topLeft.y + botRight.y) / 2 });
			}
			topRightTree->insert(node);
		}

		// Indicates botRightTree 
		else
		{
			if (!botRightTree)
			{
				botRightTree = new QuadTree(
					Point{ (topLeft.x + botRight.x) / 2,
					(topLeft.y + botRight.y) / 2 },
					Point{ botRight.x, botRight.y });
			}
			botRightTree->insert(node);
		}
	}
}

std::vector<std::tuple<Point, Point>> QuadTree::get_bounds() {
	std::vector<std::tuple<Point, Point>> boundsList{};
	std::tuple<Point, Point> coordinates{ topLeft, botRight };
	boundsList.push_back(coordinates);

	if (topLeftTree != nullptr) {
		auto sourceMap = topLeftTree->get_bounds();
		boundsList.insert(boundsList.end(), sourceMap.begin(), sourceMap.end());
	}

	if (topRightTree != nullptr) {
		auto sourceMap = topRightTree->get_bounds();
		boundsList.insert(boundsList.end(), sourceMap.begin(), sourceMap.end());
	}

	if (botLeftTree != nullptr) {
		auto sourceMap = botLeftTree->get_bounds();
		boundsList.insert(boundsList.end(), sourceMap.begin(), sourceMap.end());
	}

	if (botRightTree != nullptr) {
		auto sourceMap = botRightTree->get_bounds();
		boundsList.insert(boundsList.end(), sourceMap.begin(), sourceMap.end());
	}

	return boundsList;
}

bool QuadTree::in_boundary(Point p) {
	// check if something of object is in boundary

	// Check if something in this range is between topLeft and botRight:
	// Range:
	// x,
	// y,
	// x + width,
	// y + height,

	return (p.x >= topLeft.x &&
		p.x <= botRight.x &&
		p.y >= topLeft.y &&
		p.y <= botRight.y);
}