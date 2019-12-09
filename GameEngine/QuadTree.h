#pragma once
#include <vector>
#include <memory>

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
		std::shared_ptr<Node> nodes[15];
		int capacity = 15;

		// Children of this tree 
		std::unique_ptr<QuadTree> topLeftTree;
		std::unique_ptr<QuadTree> topRightTree;
		std::unique_ptr<QuadTree> botLeftTree;
		std::unique_ptr<QuadTree> botRightTree;
	public:
		ENGINE_API QuadTree(Point, Point);
		ENGINE_API ~QuadTree();

		ENGINE_API void insert(std::shared_ptr<Node>);
		ENGINE_API void divide(std::shared_ptr<Node>, Point&);
		ENGINE_API void divideNode(std::shared_ptr<Node> node);
		ENGINE_API bool in_boundary(std::shared_ptr<Node> node);
		ENGINE_API std::vector<std::tuple<Point, Point>> get_bounds();
		ENGINE_API std::vector<std::tuple<std::shared_ptr<Node>, std::shared_ptr<Node>>> get_collisions();
	};
}