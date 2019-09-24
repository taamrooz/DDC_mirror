#pragma once
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "EntityManager.h"
#include "BaseSystem.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

class Core
{
private:
	static Core instance_;
	std::vector<std::unique_ptr<BaseSystem>> systems_;
	std::unique_ptr<EntityManager> manager_ = nullptr;
	bool is_running_ = true;
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Surface* surf_ = nullptr;
	//The music that will be played
	Mix_Music* gMusic = NULL;

	//The sound effects that will be used
	Mix_Chunk* gScratch = NULL;
	Mix_Chunk* gHigh = NULL;
	Mix_Chunk* gMedium = NULL;
	Mix_Chunk* gLow = NULL;
	Core();
	
	bool init(const char*, int, int, bool);
	void input(SDL_Event &event);
	void update();
	void render();
	void cleanup();
	bool loadMedia();
public:
	int execute(int argc, char* argv[]);
	SDL_Renderer* get_renderer() const;
	static Core* get_instance();
};

