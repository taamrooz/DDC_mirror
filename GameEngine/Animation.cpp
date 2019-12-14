#include "Animation.h"

Animation::Animation(int frames, Texture* texture) : gSpriteSheetTexture{ texture } {
	WALKING_ANIMATION_FRAMES = frames;
	total_frames = frames;
	gSpriteClips = std::vector<Engine::rect2d>(frames);
	pause = false;
	loop = true;
}

Animation::~Animation() {
	delete gSpriteSheetTexture;
}

void Animation::UpdateAnimation(double x, double y, SDL_RendererFlip flip)
{
	//Render current frame
	Engine::rect2d* currentClip = &gSpriteClips[CURRENT_FRAME / 4];

	gSpriteSheetTexture->render(x, y, currentClip, scale, flip);

	if (!pause) {
		//Go to next frame
		CURRENT_FRAME++;

		//Cycle animation
		if (CURRENT_FRAME / total_frames >= WALKING_ANIMATION_FRAMES)
		{
			if (loop) {
				CURRENT_FRAME = 0;
			}
			else {
				pause = true;
			}
		}
	}
}
