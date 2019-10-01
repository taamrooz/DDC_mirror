#pragma once
#include "EntityManager.h"

class BaseSystem
{
protected:
	EntityManager* manager_;
public:
	virtual ~BaseSystem() = default;
	BaseSystem(EntityManager* manager) : manager_(manager) {}
	virtual void update(double dt) = 0;
};

