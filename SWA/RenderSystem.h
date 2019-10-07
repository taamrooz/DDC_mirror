#pragma once
#include "BaseSystem.h"
#include "TilemapComponent.h"

class RenderSystem :
	public BaseSystem
{
public:
	RenderSystem(EntityManager* manager, TilemapComponent* tilemapcomponent);
	TilemapComponent* tilemap_component;
	void update(double dt) override;
};

