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

void Animation::UpdateAnimation(int x, int y)
{
	//Render current frame
	SDL_Rect* currentClip = &gSpriteClips[CURRENT_FRAME / 4];

	gSpriteSheetTexture.render((x - currentClip->w) / 2, (y - currentClip->h) / 2, currentClip);
	//SDL_RenderPresent(gRenderer);

	//Go to next frame
	CURRENT_FRAME++;

	//Cycle animation
	if (CURRENT_FRAME / 4 >= WALKING_ANIMATION_FRAMES)
	{
		CURRENT_FRAME = 0;
	}

}
