#pragma once
#include "BaseSystem.h"
#include "Core.h"
#include "InputComponent.h"

class AudioSystem :
	public BaseSystem

{
public:
	AudioSystem(EntityManager* manager, InputComponent* inputcomponent);
	void update(double dt) override;
private:
	InputComponent* input_component;
};

