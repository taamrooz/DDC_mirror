#pragma once
#include "BaseSystem.h"
#include "EntityManager.h"

class MoveCharacterSystem :
	public BaseSystem

{
public:
	MoveCharacterSystem(EntityManager*);
	void update(double) override;
private:
	const double move_velocity = 8;
};