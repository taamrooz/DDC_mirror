#pragma once
#include "BaseSystem.h"
#include "EntityManager.h"
#include "InputComponent.h"

class MoveCharacterSystem :
	public BaseSystem

{
public:
	MoveCharacterSystem(EntityManager* manager, InputComponent* inputcomponent);
	void update(double dt) override;
private:
	InputComponent* input_component;
};

