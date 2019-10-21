#pragma once
#include "BaseSystem.h"
#include "Core.h"
#include "CollisionHandlers.h"
class ShootSystem :
	public BaseSystem
{
public:
	ShootSystem(EntityManager* manager);
	void update(double dt) override;
private:
	void createBullet(int xV, int yV, int x, int y);
	const int bullet_velocity = 20;
};