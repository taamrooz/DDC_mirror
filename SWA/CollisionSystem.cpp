#include "RenderSystem.h"
#include "Renderer.h"
#include "CollisionSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "QuadTree.h"
#include <vector>
#include <tuple>
#include "CollisionComponent.h"
#include "RoomComponent.h"


CollisionSystem::CollisionSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {}

void CollisionSystem::update(double dt)
{

	//Starting points of the quadtree
	Engine::Point leftTop{ 0, 0 };
	Engine::Point botRight{ 1280, 960 }; // TODO: make this not hardcoded
	Engine::QuadTree quadTree{ leftTop, botRight };

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
	quadTree.insert(new Node{ Point{395, 295}, 8, 10, 10 });

	// linksboven
	quadTree.insert(new Node{ Point{386, 286}, 9, 10, 10 });

	// rechtsonder
	quadTree.insert(new Node{ Point{405, 305}, 10, 10, 10 });

	// linskonder
	quadTree.insert(new Node{ Point{385, 305}, 11, 10, 10 });

	// Rechstonder
	quadTree.insert(new Node{ Point{405, 285}, 12, 10, 10 });
			*/

			//// <----- TEST SCENARIO ----->  ////
	for (auto entity : manager_->get_all_entities_from_current_room<CollisionComponent>())
	{
		auto positionComponent = manager_->get_component<PositionComponent>(entity);
		auto collisionComponent = manager_->get_component<CollisionComponent>(entity);
		auto velocityComponent = manager_->get_component<VelocityComponent>(entity);
		auto roomComponent = manager_->get_component<RoomComponent>(entity);

		int x = positionComponent->x;
		int y = positionComponent->y;
		if (velocityComponent != nullptr) {
			x = positionComponent->x + velocityComponent->dx;
			y = positionComponent->y + velocityComponent->dy;
		}


		quadTree.insert(new Engine::Node{ Engine::Point{ x, y }, entity, collisionComponent->width, collisionComponent->height });
	}

	std::vector<std::tuple<Engine::Node*, Engine::Node*>> collisions = quadTree.get_collisions();

	for (auto const& node_tuple : collisions) {
		Engine::Node* first_node = std::get<0>(node_tuple);
		Engine::Node* second_node = std::get<1>(node_tuple);

		//handle collision
		//gebruikt nu entity 0 omdat er nog test data in staat

		auto collisionComponent = manager_->get_component<CollisionComponent>(first_node->id);

		update_velocity(first_node, second_node);
		if (collisionComponent != nullptr && collisionComponent->collisionHandler != nullptr) {
			collisionComponent->collisionHandler(first_node->id, second_node->id, manager_);
		}
	}

	//// <----- VISUAL DEMO OF QUADTREE ----->  ////
	std::vector<std::tuple<Engine::Point, Engine::Point>> bounds = quadTree.get_bounds();
	for (auto const& point_tuple : bounds) {
		int x = std::get<0>(point_tuple).x;
		int y = std::get<0>(point_tuple).y;

		int width = std::get<1>(point_tuple).x - std::get<0>(point_tuple).x;
		int height = std::get<1>(point_tuple).y - std::get<0>(point_tuple).y;

		Engine::add_rectangle(Engine::rect2d(x, y, width, height));
	}

	//Engine::render_rectangles();
	//// <----- VISUAL DEMO OF QUADTREE ----->  ////
}

void CollisionSystem::update_velocity(Engine::Node* first_node, Engine::Node* second_node) {
	auto first_node_velocity_component = manager_->get_component<VelocityComponent>(first_node->id);
	auto first_node_position_component = manager_->get_component<PositionComponent>(first_node->id);
	auto second_node_velocity_component = manager_->get_component<VelocityComponent>(second_node->id);
	auto second_node_position_component = manager_->get_component<PositionComponent>(second_node->id);

	//TEMP if first_node is bullet and second_node is character, do not update vel (eating own bullets).
	auto collision = manager_->get_component<CollisionComponent>(first_node->id);
	if (collision != nullptr && collision->owner == second_node->id)
	{
		return;
	}
	//Vice versa
	collision = manager_->get_component<CollisionComponent>(second_node->id);
	if (collision != nullptr && collision->owner == first_node->id)
	{
		return;
	}


	if (first_node_velocity_component != nullptr && second_node_position_component != nullptr) {
		// Top bottom collisiondetection first node
		if (first_node_velocity_component->dx > 0) {
			if ((first_node_position_component->x + first_node->width) >= (second_node_position_component->x)) {
				first_node_position_component->x = second_node_position_component->x - first_node->width;
				first_node_velocity_component->dx = 0;
			}
		}
		else if (first_node_velocity_component->dx < 0) {
			if ((first_node_position_component->x) <= (second_node_position_component->x + second_node->width)) {
				first_node_position_component->x = second_node_position_component->x + second_node->width;
				first_node_velocity_component->dx = 0;
			}
		}

		// Top and bottom collisiondetection first node
		if (first_node_velocity_component->dy > 0) {
			if ((first_node_position_component->y + first_node->height) >= (second_node_position_component->y)) {
				first_node_position_component->y = second_node_position_component->y - first_node->height;
				first_node_velocity_component->dy = 0;
			}
		}
		else if (first_node_velocity_component->dy < 0) {
			if ((first_node_position_component->y) <= (second_node_position_component->y + second_node->height)) {
				first_node_position_component->y = second_node_position_component->y + second_node->height;
				first_node_velocity_component->dy = 0;
			}
		}
	}

	if (second_node_velocity_component != nullptr) {

		// Top bottom collisiondetection second node
		if (second_node_velocity_component->dx > 0) {
			if ((second_node_position_component->x + second_node->width) >= (first_node_position_component->x)) {
				second_node_position_component->x = first_node_position_component->x - second_node->width;
				second_node_velocity_component->dx = 0;
			}
		}
		else if (second_node_velocity_component->dx < 0) {
			if ((second_node_position_component->x) <= (first_node_position_component->x + first_node->width)) {
				second_node_position_component->x = first_node_position_component->x + first_node->width;
				second_node_velocity_component->dx = 0;
			}
		}


		// Top and bottom collisiondetection second node
		if (second_node_velocity_component->dy > 0) {
			if ((second_node_position_component->y + second_node->height) >= (first_node_position_component->y)) {
				second_node_position_component->y = first_node_position_component->y - second_node->height;
				second_node_velocity_component->dy = 0;
			}
		}
		else if (second_node_velocity_component->dy < 0) {
			if (second_node_position_component->y <= first_node_position_component->y + first_node->height) {
				second_node_position_component->y = first_node_position_component->y + first_node->height;
				second_node_velocity_component->dy = 0;
			}
		}
	}
}
