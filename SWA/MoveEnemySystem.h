#pragma once
#include "BaseSystem.h"
#include "EntityManager.h"

class MoveEnemySystem :
	public BaseSystem

{
public:
	MoveEnemySystem(Engine::EntityManager<Component>*);
	void update(double) override;
private:

};