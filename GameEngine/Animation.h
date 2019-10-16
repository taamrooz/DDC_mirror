#pragma once
#include "Texture.h"
#include <vector>
class Animation
{
public:
	Animation(int, std::vector<SDL_Rect>&, Texture);
	~Animation();
	/*
	 * Updates the animation by its specified x and y coordinates, and whether the animation should be flipped.
	 */
	void UpdateAnimation(double x, double y, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int CURRENT_FRAME = 0;
	double scale = 1;
	int total_frames;
	int WALKING_ANIMATION_FRAMES;
	std::vector<SDL_Rect> gSpriteClips;
	Texture gSpriteSheetTexture;
};

