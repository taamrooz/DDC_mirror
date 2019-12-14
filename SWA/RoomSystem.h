#pragma once
#include "BaseSystem.h"

class RoomSystem :
	public BaseSystem
{
public:
	RoomSystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
};
