#pragma once
#include <iostream>


#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_mixer.h>
#include <cstdio>
#include <string>
#include "EntityManager.h"
#include "BaseSystem.h"
#include "Audio.h"

class Core
{
private:
	static Core instance_;
	//AudioManager* audio_manager;
	std::vector<std::unique_ptr<BaseSystem>> systems_;
	std::unique_ptr<EntityManager> manager_ = nullptr;
	bool is_running_ = true;
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Surface* surf_ = nullptr;
	//The music that will be played
	std::string gMusic;

	//The sound effects that will be used
	std::string gScratch;
	std::string gHigh;
	std::string gMedium;
	std::string gLow;
	Core();
	
	bool init(const char*, int, int, bool);
	void input(SDL_Event &event);
	void update();
	void render();
	void cleanup();
	void loadMedia();
public:
	int execute(int argc, char* argv[]);
	SDL_Renderer* get_renderer() const;
	static Core* get_instance();
};

