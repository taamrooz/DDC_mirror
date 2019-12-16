#pragma once
#include "BaseSystem.h"
#include <vector2d.h>

class MoveSystem :
	public BaseSystem
{
public:
	MoveSystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
};

