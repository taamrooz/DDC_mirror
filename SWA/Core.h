#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include "EntityManager.h"
#include "BaseSystem.h"
#include "Audio.h"
#include "InputComponent.h"
#include "AnimationComponent.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"

class Core
{
private:
	static Core instance_;
	std::vector<std::unique_ptr<BaseSystem>> systems_;
	std::unique_ptr<EntityManager> manager_ = nullptr;
	std::unique_ptr<InputComponent> input_component_ = nullptr;
	bool is_running_ = true;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Surface* surf_ = nullptr;

	Core();
	bool init(const char*, int, int, bool);
	void update();
	void render();
	void cleanup();
public:
	int execute(int argc, char* argv[]);


	static Core* get_instance();
	void StopGameLoop();
};

