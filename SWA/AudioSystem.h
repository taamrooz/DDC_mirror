#pragma once
#include "BaseSystem.h"
#include "Core.h"

class AudioSystem :
	public BaseSystem

{
public:
	AudioSystem(EntityManager* manager);
	void update(double dt) override;
};

