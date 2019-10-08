#include "RenderSystem.h"
#include "Renderer.h"
#include "CollisionSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "QuadTree.h"
#include <vector>
#include <tuple>


CollisionSystem::CollisionSystem(EntityManager* manager) : BaseSystem(manager) {}

void CollisionSystem::update(double dt)
{
	Point leftTop{ 0, 0 };
	Point botRight{ 800, 600 };
	QuadTree quadTree{ leftTop, botRight };

	Node leftTopNode{ Point{150, 200}, 10, 1 };
	Node leftBotNode{ Point{ 450, 200 }, 10, 1 };
	Node rightTopNode{ Point{ 150, 600 }, 10, 1 };
	Node rightBotNode{ Point{ 450, 600 }, 10, 1 };

	quadTree.insert(&leftTopNode);
	quadTree.insert(&leftBotNode);
	quadTree.insert(&rightTopNode);
	quadTree.insert(&rightBotNode);

	quadTree.insert(&Node{ Point{160, 200}, 10, 1 });
	quadTree.insert(&Node{ Point{170, 200}, 10, 1 });
	quadTree.insert(&Node{ Point{180, 200}, 10, 1 });
	quadTree.insert(&Node{ Point{175, 200}, 10, 1 });


	std::vector<std::tuple<Point, Point>> bounds = quadTree.get_bounds();
	int i = 0;
	for (auto const& point_tuple : bounds) {
		int x = std::get<0>(point_tuple).x;
		int y = std::get<0>(point_tuple).y;

		int width = std::get<1>(point_tuple).x - std::get<0>(point_tuple).x;
		int height = std::get<1>(point_tuple).y - std::get<0>(point_tuple).y;

		Engine::AddRectangle(x, y, width, height);
	}

	Engine::RenderRectangles();

	/*
	for (auto entity : manager_->get_all_entities<VelocityComponent>())
	{


		auto position = manager_->get_component<PositionComponent>(entity);
		std::cout << position.x << std::endl;
		auto velocity = manager_->get_component<VelocityComponent>(entity);
	}
	*/
}
