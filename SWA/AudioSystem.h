#pragma once
#include "BaseSystem.h"
#include "Core.h"

class AudioSystem :
	public BaseSystem

{
public:
	AudioSystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
};

