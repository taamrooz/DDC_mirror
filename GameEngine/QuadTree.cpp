#include "QuadTree.h"
#include <vector>
#include <tuple>

using namespace Engine;

Point::Point(int _x, int _y) {
	x = _x;
	y = _y;
}

Node::Node(Point _position, uint32_t _id, int _width, int _height) : position(_position), id(_id), width(_width), height(_height) {
}

QuadTree::QuadTree(Point topL, Point botR) :
	topLeftTree(nullptr), topRightTree(nullptr), botLeftTree(nullptr), botRightTree(nullptr),
	topLeft(topL), botRight(botR) {
}

QuadTree::~QuadTree() {
	for (size_t i = 0; i < capacity; i++)
	{
		if (nodes[i]) {
			delete nodes[i];
			nodes[i] = nullptr;
		}
	}

	delete topLeftTree;
	delete topRightTree;
	delete botLeftTree;
	delete botRightTree;
}

void QuadTree::insert(Node* node) {
	if (!node) {
		return;
	}

	if (!in_boundary(node)) {
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

		if (nodes[i]->id == node->id) {
			delete node;
			return;
		}
	}

	if (!added) {
		if (!topLeftTree && !topRightTree && !botLeftTree && !botRightTree) {
			// subdivide all nodes
			for (int i = 0; i < capacity; ++i) {
				//divide(nodes[i], &nodes[i]->position);
				divideNode(nodes[i]);
			}
		}

		// subdivde node
		//divide(node, &node->position);
		divideNode(node);
		delete node;
	}
}

void QuadTree::divideNode(Node* node) {
	// subdivde node
	Point* topLeft = new Point{ node->position.x, node->position.y };
	Point* topRight = new Point{ (node->position.x + node->width), node->position.y };
	Point* botLeft = new Point{ node->position.x, (node->position.y + node->height) };
	Point* botRight = new Point{ (node->position.x + node->width), (node->position.y + node->height) };

	Node* topLeftNode = new Node(node->position, node->id, node->width, node->height);
	Node* topRightNode = new Node(node->position, node->id, node->width, node->height);
	Node* botLetNode = new Node(node->position, node->id, node->width, node->height);
	Node* botRightNode = new Node(node->position, node->id, node->width, node->height);

	divide(topLeftNode, topLeft);
	divide(topRightNode, topRight);
	divide(botLetNode, botLeft);
	divide(botRightNode, botRight);

	delete topLeft;
	delete topRight;
	delete botLeft;
	delete botRight;
}

void QuadTree::divide(Node* node, Point* p) {
	if ((topLeft.x + botRight.x) / 2 >= p->x)
	{
		// Indicates topLeftTree 
		if ((topLeft.y + botRight.y) / 2 >= p->y)
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
		if ((topLeft.y + botRight.y) / 2 >= p->y)
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


std::vector<std::tuple<Node*, Node*>> QuadTree::get_collisions() {
	std::vector<std::tuple<Node*, Node*>> collisions_list{};

	bool shouldFindCollision = true;
	if (topLeftTree)
	{
		std::vector<std::tuple<Node*, Node*>> tree_collisions = topLeftTree->get_collisions();
		if (!tree_collisions.empty()) {
			if (collisions_list.empty()) {
				collisions_list = tree_collisions;
			}
			else {
				collisions_list.insert(collisions_list.end(), tree_collisions.begin(), tree_collisions.end());
			}
		}
		shouldFindCollision = false;
	}

	if (topRightTree)
	{
		std::vector<std::tuple<Node*, Node*>> tree_collisions = topRightTree->get_collisions();
		if (!tree_collisions.empty()) {
			if (collisions_list.empty()) {
				collisions_list = tree_collisions;
			}
			else {
				tree_collisions.begin();
				tree_collisions.end();
				collisions_list.insert(collisions_list.end(), tree_collisions.begin(), tree_collisions.end());
			}
		}
		shouldFindCollision = false;
	}

	if (botLeftTree)
	{
		std::vector<std::tuple<Node*, Node*>> tree_collisions = botLeftTree->get_collisions();
		if (!tree_collisions.empty()) {
			if (collisions_list.empty()) {
				collisions_list = tree_collisions;
			}
			else {
				collisions_list.insert(collisions_list.end(), tree_collisions.begin(), tree_collisions.end());
			}
		}
		shouldFindCollision = false;
	}

	if (botRightTree)
	{
		std::vector<std::tuple<Node*, Node*>> tree_collisions = botRightTree->get_collisions();
		if (!tree_collisions.empty()) {
			if (collisions_list.empty()) {
				collisions_list = tree_collisions;
			}
			else {
				collisions_list.insert(collisions_list.end(), tree_collisions.begin(), tree_collisions.end());
			}
		}
		shouldFindCollision = false;
	}

	if (shouldFindCollision)
	{
		for (size_t i = 0; i < capacity; i++)
		{
			if (nodes[i]) {
				for (size_t x = 0; x < capacity; x++)
				{
					if (nodes[x]) {
						if (nodes[i]->id == nodes[x]->id) {
							// should not check collision with itself
							continue;
						}
						else {
							int node_a_x1 = nodes[i]->position.x;
							int node_a_x2 = node_a_x1 + nodes[i]->width;

							int node_b_x1 = nodes[x]->position.x;
							int node_b_x2 = node_b_x1 + nodes[x]->width;

							int node_a_y1 = nodes[i]->position.y;
							int node_a_y2 = node_a_y1 + nodes[i]->height;

							int node_b_y1 = nodes[x]->position.y;
							int node_b_y2 = node_b_y1 + nodes[x]->height;


							if (node_a_x1 < node_b_x2 && node_a_x2 > node_b_x1&&
								node_a_y1 < node_b_y2 && node_a_y2 > node_b_y1) {
								std::tuple<Node*, Node*> collision{ nodes[i], nodes[x] };
								collisions_list.push_back(collision);
							}
						}
					}
				}

			}
		}
	}

	return collisions_list;
}

bool QuadTree::in_boundary(Node* node) {
	// check if something of object is in boundary

	// Check if something in this range is between topLeft and botRight:
	// Range:
	// x,
	// y,
	// x + width,
	// y + height,

	int node_a_x1 = node->position.x;
	int node_a_x2 = node_a_x1 + node->width;

	int node_b_x1 = topLeft.x;
	int node_b_x2 = botRight.x;

	int node_a_y1 = node->position.y;
	int node_a_y2 = node_a_y1 + node->height;

	int node_b_y1 = topLeft.y;
	int node_b_y2 = botRight.y;

	return (node_a_x1 <= node_b_x2 && node_a_x2 >= node_b_x1 &&
		node_a_y1 <= node_b_y2 && node_a_y2 >= node_b_y1);
}