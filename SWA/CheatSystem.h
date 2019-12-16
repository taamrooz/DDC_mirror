#pragma once
#include "BaseSystem.h"
class Core;

class CheatSystem :
	public BaseSystem
{
public:
	CheatSystem(Engine::EntityManager<Component>* manager, Core& core);
	void update(double dt) override;
private:
	Core* core_;
};

