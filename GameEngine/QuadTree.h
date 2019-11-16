#pragma once
#include <vector>

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine {
	struct Point
	{
		int x;
		int y;
		ENGINE_API Point(int, int);
	};

	// The objects that we want stored in the quadtree 
	struct Node
	{
		Point position;
		uint32_t id;
		int width;
		int height;
		ENGINE_API Node(Point, uint32_t, int, int);
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
		ENGINE_API QuadTree(Point, Point);
		ENGINE_API ~QuadTree();

		ENGINE_API void insert(Node*);
		ENGINE_API void divide(Node*, Point*);
		ENGINE_API void divideNode(Node*);
		ENGINE_API bool in_boundary(Node*);
		ENGINE_API std::vector<std::tuple<Point, Point>> get_bounds();
		ENGINE_API std::vector<std::tuple<Node*, Node*>> get_collisions();
	};
}