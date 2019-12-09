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


CollisionSystem::CollisionSystem(Engine::EntityManager<Component>* manager, Core& core) : BaseSystem(manager) {
	CollisionSystem::core = &core;
}

void CollisionSystem::update(double dt)
{
	//Starting points of the quadtree
	Engine::Point leftTop{ 0, 0 };
	Engine::Point botRight{ 1280, 960 }; // TODO: make this not hardcoded
	Engine::QuadTree quadTree{ leftTop, botRight };

	// Create nodes for QuadTree based on all collidable entities
	for (auto entity : manager_->get_all_entities_from_current_room<CollisionComponent>())
	{
		auto positionComponent = manager_->get_component<PositionComponent>(entity);
		auto collisionComponent = manager_->get_component<CollisionComponent>(entity);
		auto velocityComponent = manager_->get_component<VelocityComponent>(entity);
		auto roomComponent = manager_->get_component<RoomComponent>(entity);

		int x = positionComponent->x;
		int y = positionComponent->y;
		if (velocityComponent != nullptr) {
			x += velocityComponent->dx;
			y += velocityComponent->dy;
		}

		std::shared_ptr<Engine::Node> node{ new Engine::Node{Engine::Point{ x, y }, entity, collisionComponent->width, collisionComponent->height} };

		quadTree.insert(node);
	}

	// Get all collisions the QuadTree detected
	std::vector<std::tuple<std::shared_ptr<Engine::Node>, std::shared_ptr<Engine::Node>>> collisions = quadTree.get_collisions();

	// Loop over collisions to handle collision
	for (auto const& node_tuple : collisions) {
		std::shared_ptr<Engine::Node> first_node = std::get<0>(node_tuple);
		std::shared_ptr<Engine::Node> second_node = std::get<1>(node_tuple);

		auto collisionComponent = manager_->get_component<CollisionComponent>(first_node->id);

		// Call collision handler
		if (collisionComponent != nullptr && collisionComponent->collisionHandler != nullptr) {
			collisionComponent->collisionHandler(first_node->id, second_node->id, manager_, core);
		}
	}
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
