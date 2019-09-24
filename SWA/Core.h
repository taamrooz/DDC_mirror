#pragma once
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
class Core
{
private:
	static Core Instance;
	bool isRunning = true;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surf = nullptr;
	Core();
	
	bool init(const char*, int, int, bool);
	void input(const SDL_Event&);
	void update();
	void render();
	void cleanup();
public:
	int execute(int argc, char* argv[]);
	SDL_Renderer* get_renderer() const;
	static Core* getInstance();
};

