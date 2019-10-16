#include "Animation.h"

Animation::Animation(int frames, std::vector<SDL_Rect>& spriteclips, Texture texture) : gSpriteSheetTexture{texture} {
	WALKING_ANIMATION_FRAMES = frames;
	//gSpriteSheetTexture = texture;
	gSpriteClips = spriteclips;
}

Animation::~Animation() {
	gSpriteSheetTexture = nullptr;
	gSpriteClips.clear();
}

void Animation::UpdateAnimation(double x, double y, SDL_RendererFlip flip)
{
	//Render current frame
	SDL_Rect* currentClip = &gSpriteClips[CURRENT_FRAME / 4];

	gSpriteSheetTexture.render((x - currentClip->w), (y - currentClip->h), currentClip, scale, flip);

	//Go to next frame
	CURRENT_FRAME++;

	//Cycle animation
	if (CURRENT_FRAME / WALKING_ANIMATION_FRAMES >= WALKING_ANIMATION_FRAMES)
	{
		CURRENT_FRAME = 0;
	}

}
