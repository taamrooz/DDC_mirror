#pragma once
#include "BaseSystem.h"

class MoveSystem :
	public BaseSystem
{
public:
	MoveSystem(EntityManager* manager);
	void update(double dt) override;
};

