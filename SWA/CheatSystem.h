#pragma once
#include "BaseSystem.h"
#include "Core.h"
class CheatSystem :
	public BaseSystem
{
public:
	CheatSystem(Engine::EntityManager<Component>* manager, Core& core);
	void update(double dt) override;
private:
	Core* core;
};

