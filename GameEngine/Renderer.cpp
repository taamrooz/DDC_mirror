#include "renderer.h"
#include <iostream>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surf;

//std::vector<Animation*> animations;

//int frames, std::string path, SDL_Window* window, SDL_Renderer* renderer
bool Engine::InitRenderer(std::string title, bool fullscreen, Uint32 width, Uint32 height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Unable to initialize SDL" << std::endl;
		return false;
	}
	auto flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if ((window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags)) == nullptr)
	{
		std::cout << "Unable to initialize Window" << std::endl;
		return false;
	}
	surf = SDL_GetWindowSurface(window);
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
	{
		std::cout << "Unable to initialize renderer" << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (!(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG))
	{
		std::cout << IMG_GetError() << std::endl;
		std::cout << "Unable to initialize Image" << std::endl;
		return false;
	}
	return true;
}

Animation& Engine::LoadAnimation(std::string path) {

	auto WALKING_ANIMATION_FRAMES = 4;
	auto gSpriteClips = std::vector<SDL_Rect>(4);
	auto texture = new Texture(renderer);
	auto animation = new Animation(WALKING_ANIMATION_FRAMES, gSpriteClips, *texture);
	texture->free();
	//animations.push_back(animation.get());

	//Load media
	if (!Engine::LoadSpriteSheet(path, animation))
	{
		printf("Failed to load media!\n");
	}

	return *animation;
}

bool Engine::LoadSpriteSheet(std::string path, Animation* animation)
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!animation->gSpriteSheetTexture.loadFromFile(path))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		int height = animation->gSpriteSheetTexture.getHeight();
		int width = animation->gSpriteSheetTexture.getWidth() / animation->WALKING_ANIMATION_FRAMES;
		for (int i = 0; i < animation->WALKING_ANIMATION_FRAMES; i++) {
			animation->gSpriteClips[i].x = width * i;
			animation->gSpriteClips[i].y = 0;
			animation->gSpriteClips[i].w = width;
			animation->gSpriteClips[i].h = animation->gSpriteSheetTexture.getHeight();
		}
	}

	return success;
}


const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

void Engine::RenderClear() {
	SDL_RenderClear(renderer);
}

void Engine::Render() {
	SDL_UpdateWindowSurface(window);
	SDL_RenderPresent(renderer);
	
	frameStart = SDL_GetTicks();
	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
}

void Engine::UpdateAnimation(Animation* a)
{
	a->UpdateAnimation();	
}

void Engine::DestroyRenderer() {
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}