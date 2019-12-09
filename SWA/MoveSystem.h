#pragma once
#include "BaseSystem.h"
#include <vector2d.h>

class MoveSystem :
	public BaseSystem
{
public:
	MoveSystem(Engine::EntityManager<Component>* manager);
	bool intersects(vector2d a1, vector2d a2, vector2d b1, vector2d b2, vector2d& intersection);
	int direction(vector2d a, vector2d b, vector2d c);
	void update(double dt) override;
};

