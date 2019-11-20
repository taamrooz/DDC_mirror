#pragma once
#include "BaseSystem.h"
#include "QuadTree.h"
#include "Core.h"

class CollisionSystem :
	public BaseSystem
{
public:
	CollisionSystem(Engine::EntityManager<Component>* manager, Core& core);
	void update(double dt) override;
	void update_velocity(Engine::Node* first_node, Engine::Node* second_node);
private:
	Core* core;
};

