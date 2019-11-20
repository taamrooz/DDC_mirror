#pragma once
#include "EntityManager.h"
#include "Component.h"

class BaseSystem
{
protected:
	Engine::EntityManager<Component>* manager_;
public:
	virtual ~BaseSystem() = default;
	BaseSystem(Engine::EntityManager<Component>* manager) : manager_(manager) {}
	virtual void update(double dt) = 0;
};

