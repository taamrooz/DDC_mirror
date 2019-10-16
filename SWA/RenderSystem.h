#pragma once
#include "BaseSystem.h"

class RenderSystem :
	public BaseSystem
{
public:
	RenderSystem(EntityManager* manager);
	void update(double dt) override;
};

