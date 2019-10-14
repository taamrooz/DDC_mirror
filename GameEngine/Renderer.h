#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Texture.h"
#include "Animation.h"


#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine {
	ENGINE_API bool InitRenderer(std::string, bool, Uint32, Uint32);
	ENGINE_API void UpdateAnimation(Animation*, bool, bool);
	ENGINE_API bool LoadSpriteSheet(std::string path, Animation*);
	ENGINE_API Animation& LoadAnimation(std::string path, int frames);
	ENGINE_API void DestroyRenderer();
	ENGINE_API void Render();
	ENGINE_API void RenderClear();

	ENGINE_API void AddRectangle(int x, int y, int w, int h);
	ENGINE_API void RenderRectangles();
}