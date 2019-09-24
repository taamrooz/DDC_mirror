#pragma once
#include "EntityManager.h"

class BaseSystem
{
protected:
	EntityManager* manager;
public:
	virtual ~BaseSystem() = default;
	BaseSystem(EntityManager* manager) : manager(manager) {}
	virtual void update(double dt) = 0;
};

