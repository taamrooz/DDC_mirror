#pragma once
#include "BaseSystem.h"
#include "EntityManager.h"
#include "QuadTree.h"
class MoveEnemySystem :
	public BaseSystem

{
public:
	MoveEnemySystem(Engine::EntityManager<Component>*);
	void update(double) override;
private:

};