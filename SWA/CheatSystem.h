#pragma once
#include "BaseSystem.h"
class CheatSystem :
	public BaseSystem
{
public:
	CheatSystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
};

