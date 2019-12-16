#pragma once
#include "BaseSystem.h"
#include "Core.h"

class ShootSystem :
	public BaseSystem
{
public:
	ShootSystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
private:
	void createBullet(int xV, int yV, int x, int y, double dt);
	const int bullet_velocity = 20;
};