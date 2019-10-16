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
	ENGINE_API void UpdateAnimation(Animation* a, double, double, bool, bool);
	ENGINE_API bool LoadSpriteSheet(std::string path, Animation*);
	ENGINE_API Animation& LoadAnimation(std::string path, int frames);
	ENGINE_API Texture* LoadTileset(std::string path);
	ENGINE_API void RenderTile(int xpos, int ypos, int width, int height, int xclip, int yclip, Texture* texture);
	ENGINE_API void DestroyRenderer();
	ENGINE_API void Render(int framestart);
	ENGINE_API int PreUpdate();

	ENGINE_API void AddRectangle(int x, int y, int w, int h);
	ENGINE_API void RenderRectangles();
}