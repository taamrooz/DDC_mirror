#pragma once
#include "BaseSystem.h"
#include "EntityManager.h"
#include "InputComponent.h"

class MoveCharacterSystem :
	public BaseSystem

{
public:
	MoveCharacterSystem(EntityManager*, InputComponent*);
	void update(double) override;
private:
	InputComponent* input_component;
	const double move_velocity = 20;
};