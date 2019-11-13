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
	const double diagonal_move_velocity = sqrt(pow(move_velocity, 2.0) * 2) / 2;
};