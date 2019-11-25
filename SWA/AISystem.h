#pragma once
#include "BaseSystem.h"
#include "Core.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

class AISystem :
	public BaseSystem

{
public:
	AISystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
	int calculateDistance(int x1, int x2);
};
