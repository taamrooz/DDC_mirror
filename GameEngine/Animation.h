#pragma once
#include "Texture.h"
#include <vector>
class Animation
{
public:
	Animation(int, std::vector<SDL_Rect>&, Texture);
	~Animation();
	void UpdateAnimation(double, double, SDL_RendererFlip = SDL_FLIP_NONE);
	int CURRENT_FRAME = 0;
	int scale = 1;
	int total_frames;
	int WALKING_ANIMATION_FRAMES;
	std::vector<SDL_Rect> gSpriteClips;
	Texture gSpriteSheetTexture;
};

