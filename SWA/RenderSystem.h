#pragma once
#include "BaseSystem.h"
#include "Texture.h"

class RenderSystem :
	public BaseSystem
{
private:
	std::unique_ptr<Texture> _level_hud = nullptr;
public:
	RenderSystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
};

