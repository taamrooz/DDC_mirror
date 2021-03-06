#pragma once
#include "Texture.h"
#include <vector>
#include "rect2d.h"

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
class Animation
{
public:
	ENGINE_API Animation(int, Texture*);
	ENGINE_API ~Animation();
	/*
	 * Updates the animation by its specified x and y coordinates, and whether the animation should be flipped.
	 */
	void UpdateAnimation(double x, double y, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int CURRENT_FRAME = 0;
	double scale = 1;
	int total_frames;
	bool loop;
	bool pause;
	int WALKING_ANIMATION_FRAMES;
	std::vector<Engine::rect2d> gSpriteClips;
	Texture* gSpriteSheetTexture;
};

