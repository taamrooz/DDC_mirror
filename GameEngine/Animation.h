#pragma once
#include "Texture.h"
#include <vector>
class Animation
{
public:
	Animation(int, std::vector<SDL_Rect>&, Texture);
	~Animation();
	void UpdateAnimation();
	int CURRENT_FRAME = 0;
	int WALKING_ANIMATION_FRAMES;
	std::vector<SDL_Rect> gSpriteClips;
	Texture gSpriteSheetTexture;
};
