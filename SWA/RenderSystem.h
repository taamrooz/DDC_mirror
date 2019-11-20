#pragma once
#include "BaseSystem.h"

class RenderSystem :
	public BaseSystem
{
public:
	RenderSystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
};

