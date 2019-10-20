#include "RenderSystem.h"
#include "Renderer.h"
#include "CollisionSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "QuadTree.h"
#include <vector>
#include <tuple>
#include "CollisionComponent.h"


CollisionSystem::CollisionSystem(EntityManager* manager) : BaseSystem(manager) {}

void CollisionSystem::update(double dt)
{
	//Starting points of the quadtree
	Point leftTop{ 0, 0 };
	Point botRight{ 1280, 960 }; // TODO: make this not hardcoded
	QuadTree quadTree{ leftTop, botRight };

	//// <----- TEST SCENARIO ----->  ////
	/*
	Node leftTopNode{ Point{130, 200}, 1, 10, 10 };
	Node leftBotNode{ Point{ 450, 200 }, 2, 10, 10 };
	Node rightTopNode{ Point{ 150, 600 }, 3, 10, 10 };
	Node rightBotNode{ Point{ 450, 600 }, 4, 10, 10 };

	quadTree.insert(&leftTopNode);
	quadTree.insert(&leftBotNode);
	quadTree.insert(&rightTopNode);
	quadTree.insert(&rightBotNode);

	// Quadtree showcase scenario
	quadTree.insert(&Node{ Point{160, 200}, 5, 10, 10 });
	quadTree.insert(&Node{ Point{170, 200}, 6, 10, 10 });
	quadTree.insert(&Node{ Point{180, 200}, 7, 10, 10 });
	quadTree.insert(&Node{ Point{175, 200}, 8, 10, 10 });
	
	// Special scenario
	quadTree.insert(&Node{ Point{395, 295}, 8, 10, 10 });

	// linksboven
	quadTree.insert(&Node{ Point{386, 286}, 9, 10, 10 });

	// rechtsonder
	quadTree.insert(&Node{ Point{405, 305}, 10, 10, 10 });

	// linskonder
	quadTree.insert(&Node{ Point{385, 305}, 11, 10, 10 });

	// Rechstonder
	quadTree.insert(&Node{ Point{405, 285}, 12, 10, 10 });
	*/
	//// <----- TEST SCENARIO ----->  ////

	for (auto entity : manager_->get_all_entities<CollisionComponent>())
	{
		auto positionComponent = manager_->get_component<PositionComponent>(entity);
		auto collisionComponent = manager_->get_component<CollisionComponent>(entity);
		Node* node = new Node{ Point{ positionComponent->x, positionComponent->y }, entity, collisionComponent->width, collisionComponent->height };
		quadTree.insert(node);
	}

	std::vector<std::tuple<Node*, Node*>> collisions = quadTree.get_collisions();

	for (auto const& node_tuple : collisions) {
		Node* first_node = std::get<0>(node_tuple);
		Node* second_node = std::get<1>(node_tuple);

		update_velocity(first_node, second_node);
	}


	//// <----- VISUAL DEMO OF QUADTREE ----->  ////
	std::vector<std::tuple<Point, Point>> bounds = quadTree.get_bounds();
	for (auto const& point_tuple : bounds) {
		int x = std::get<0>(point_tuple).x;
		int y = std::get<0>(point_tuple).y;

		int width = std::get<1>(point_tuple).x - std::get<0>(point_tuple).x;
		int height = std::get<1>(point_tuple).y - std::get<0>(point_tuple).y;

		Engine::AddRectangle(x, y, width, height);
	}

	//Engine::RenderRectangles();
	//// <----- VISUAL DEMO OF QUADTREE ----->  ////
}

void CollisionSystem::update_velocity(Node* first_node, Node* second_node) {
	auto first_node_velocity_component = manager_->get_component<VelocityComponent>(first_node->id);
	auto first_node_position_component = manager_->get_component<PositionComponent>(first_node->id);
	auto second_node_velocity_component = manager_->get_component<VelocityComponent>(second_node->id);
	auto second_node_position_component = manager_->get_component<PositionComponent>(second_node->id);
	
	// check velocity
		// NEW STRATEGY check which side is touching
		// set back
	if (first_node_velocity_component->dx > 0) {
		if ((first_node_position_component->x + first_node->width) >= (second_node_position_component->x)) {
			first_node_position_component->x = second_node_position_component->x - first_node->width - 1;
		}
	} else if (first_node_velocity_component->dx < 0) {
		if ((first_node_position_component->x) <= (second_node_position_component->x + second_node->width)) {
			first_node_position_component->x = second_node_position_component->x + second_node->width + 17;
		}
	}

	if (second_node_velocity_component->dx > 0) {
		if ((second_node_position_component->x + second_node->width) >= (first_node_position_component->x)) {
			second_node_position_component->x = first_node_position_component->x - second_node->width - 1;
		}
	}
	else if (first_node_velocity_component->dx < 0) {
		if ((first_node_position_component->x) <= (second_node_position_component->x + second_node->width)) {
			first_node_position_component->x = second_node_position_component->x + second_node->width + 17;
		}
	}

	first_node_velocity_component->dx = 0;
	second_node_velocity_component->dx = 0;

	/*
	// check if first node has velocity
		// set back first node
	if (first_node_velocity_component->dx > 0 && second_node_position_component->x > first_node_position_component->x) {
		// set back vertical
		first_node_position_component->x = second_node_position_component->x - first_node->width - 1;
	} else if (first_node_velocity_component->dx < 0 && second_node_position_component->x < first_node_position_component->x) {
		// set back vertical
		first_node_position_component->x = second_node_position_component->x + second_node->width + 1;
	}

	if (first_node_velocity_component->dy > 0 && second_node_position_component->y > first_node_position_component->y) {
		//set back horizontal
		first_node_position_component->y = second_node_position_component->y - first_node->height - 1;
	}
	else if (first_node_velocity_component->dy < 0 && second_node_position_component->y < first_node_position_component->y) {
		first_node_position_component->y = second_node_position_component->y + second_node->height + 1;
	}
		*/

	// check if second node has velocity
		// set back second node
}
