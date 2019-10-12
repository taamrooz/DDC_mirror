#pragma once
#include "BaseSystem.h"
#include "Core.h"
#include "InputComponent.h"

class ShootSystem :
	public BaseSystem

{
public:
	ShootSystem(EntityManager* manager, InputComponent* inputcomponent);
	void update(double dt) override;
private:
	InputComponent* input_component;
	void createBullet(int x, int y, int xV, int yV);
};