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

QuadTree::QuadTree(Point top_l, Point bot_r) :
	top_left_tree(nullptr), top_right_tree(nullptr), bot_left_tree(nullptr), bot_right_tree(nullptr),
	topLeft(top_l), botRight(bot_r) {
}

QuadTree::~QuadTree() {

}

void QuadTree::insert(std::shared_ptr<Node> node) {
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
			//delete node;
			return;
		}
	}

	if (!added) {
		if (!top_left_tree && !top_right_tree && !bot_left_tree && !bot_right_tree) {
			// subdivide all nodes
			for (int i = 0; i < capacity; ++i) {
				//divide(nodes[i], &nodes[i]->position);
				divide_node(nodes[i]);
			}
		}

		// subdivde node
		//divide(node, &node->position);
		divide_node(node);
		// delete node;
	}
}

void QuadTree::divide_node(std::shared_ptr<Node> node) {
	// subdivde node
	Point topLeft{ node->position.x, node->position.y } ;
	Point topRight{ (node->position.x + node->width), node->position.y } ;
	Point botLeft{ node->position.x, (node->position.y + node->height) } ;
	Point botRight{ (node->position.x + node->width), (node->position.y + node->height) } ;

	divide(node, topLeft);
	divide(node, topRight);
	divide(node, botLeft);
	divide(node, botRight);
}

void QuadTree::divide(std::shared_ptr<Node> node, Point& p) {
	if ((topLeft.x + botRight.x) / 2 >= p.x)
	{
		// Indicates topLeftTree 
		if ((topLeft.y + botRight.y) / 2 >= p.y)
		{
			if (!top_left_tree)
			{
				top_left_tree = std::make_unique<QuadTree>(
					Point{ topLeft.x, topLeft.y },
					Point{ (topLeft.x + botRight.x) / 2,
					(topLeft.y + botRight.y) / 2 });
			}
			top_left_tree->insert(node);
		}

		// Indicates botLeftTree 
		else
		{
			if (!bot_left_tree)
			{
				bot_left_tree = std::make_unique<QuadTree>(
					Point{ topLeft.x,
					(topLeft.y + botRight.y) / 2 },
					Point{ (topLeft.x + botRight.x) / 2,
						botRight.y });
			}
			bot_left_tree->insert(node);
		}
	}
	else
	{
		// Indicates topRightTree 
		if ((topLeft.y + botRight.y) / 2 >= p.y)
		{
			if (!top_right_tree)
			{
				top_right_tree = std::make_unique<QuadTree>(
					Point{ (topLeft.x + botRight.x) / 2,
						topLeft.y },
					Point{ botRight.x,
					(topLeft.y + botRight.y) / 2 });
			}
			top_right_tree->insert(node);
		}

		// Indicates botRightTree 
		else
		{
			if (!bot_right_tree)
			{
				bot_right_tree = std::make_unique<QuadTree>(
					Point{ (topLeft.x + botRight.x) / 2,
					(topLeft.y + botRight.y) / 2 },
					Point{ botRight.x, botRight.y });
			}
			bot_right_tree->insert(node);
		}
	}
}

std::vector<std::tuple<Point, Point>> QuadTree::get_bounds() {
	std::vector<std::tuple<Point, Point>> boundsList{};
	std::tuple<Point, Point> coordinates{ topLeft, botRight };
	boundsList.push_back(coordinates);

	if (top_left_tree != nullptr) {
		auto sourceMap = top_left_tree->get_bounds();
		boundsList.insert(boundsList.end(), sourceMap.begin(), sourceMap.end());
	}

	if (top_right_tree != nullptr) {
		auto sourceMap = top_right_tree->get_bounds();
		boundsList.insert(boundsList.end(), sourceMap.begin(), sourceMap.end());
	}

	if (bot_left_tree != nullptr) {
		auto sourceMap = bot_left_tree->get_bounds();
		boundsList.insert(boundsList.end(), sourceMap.begin(), sourceMap.end());
	}

	if (bot_right_tree != nullptr) {
		auto sourceMap = bot_right_tree->get_bounds();
		boundsList.insert(boundsList.end(), sourceMap.begin(), sourceMap.end());
	}

	return boundsList;
}


std::vector<std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>>> QuadTree::get_collisions() {
	std::vector<std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>>> collisions_list{};

	bool shouldFindCollision = true;
	if (top_left_tree)
	{
		std::vector<std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>>> tree_collisions = top_left_tree->get_collisions();
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

	if (top_right_tree)
	{
		std::vector<std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>>> tree_collisions = top_right_tree->get_collisions();
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

	if (bot_left_tree)
	{
		std::vector<std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>>> tree_collisions = bot_left_tree->get_collisions();
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

	if (bot_right_tree)
	{
		std::vector<std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>>> tree_collisions = bot_right_tree->get_collisions();
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
								std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>> collision{ nodes[i], nodes[x] };
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

bool QuadTree::in_boundary(std::shared_ptr<Node> node) {
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