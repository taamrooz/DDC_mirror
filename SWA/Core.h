#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include "EntityManager.h"
#include "BaseSystem.h"
#include "Audio.h"
#include "AnimationComponent.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "BaseScene.h"

class Core : virtual public BaseScene
{
private:
	std::vector<std::unique_ptr<BaseSystem>> systems_;
	std::unique_ptr<EntityManager> manager_ = nullptr;
	void update();
	
public:
	Core(SceneManager* manager);
	~Core();
	bool init() override;
	void render() override;
	void cleanup() override;
	void StopGameLoop();
};

