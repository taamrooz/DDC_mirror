#pragma once
#include "BaseSystem.h"
#include "Core.h"
#include "InputComponent.h"

class InputSystem :
	public BaseSystem

{
public:
	InputSystem(EntityManager* manager, InputComponent* inputcomponent, Core &core);
	void update(double dt) override;
private:
	Core* core;
	InputComponent* input_component;
};

