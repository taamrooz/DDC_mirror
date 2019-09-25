/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "AnimationFacade.h"


//Texture wrapper class


	//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions

			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		//SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w * 4;
		renderQuad.h = clip->h * 4;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

AnimationFacade::AnimationFacade(int frames, std::string path, SDL_Window* window, SDL_Renderer* renderer) {
	WALKING_ANIMATION_FRAMES = frames;
	//Start up SDL and create window
	gWindow = window;
	gRenderer = SDL_GetRenderer(window);
	gSpriteClips = std::vector<SDL_Rect>(frames);
	//Load media
	if (!loadMedia(path))
	{
		printf("Failed to load media!\n");
	}
}

bool AnimationFacade::loadMedia(std::string path)
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile(path))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		int height = gSpriteSheetTexture.getHeight();
		int width = gSpriteSheetTexture.getWidth() / WALKING_ANIMATION_FRAMES;
		for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
			gSpriteClips[i].x = width * i;
			gSpriteClips[i].y = 0;
			gSpriteClips[i].w = width;
			gSpriteClips[i].h = gSpriteSheetTexture.getHeight();
		}
	}

	return success;
}

void AnimationFacade::updateAnimation()
{
	//Render current frame
	SDL_Rect* currentClip = &gSpriteClips[CURRENT_FRAME / 4];

	gSpriteSheetTexture.render((640 - currentClip->w) / 2, (480 - currentClip->h) / 2, currentClip);
	//SDL_RenderPresent(gRenderer);

	//Go to next frame
	CURRENT_FRAME++;

	//Cycle animation
	if (CURRENT_FRAME / 4 >= WALKING_ANIMATION_FRAMES)
	{
		CURRENT_FRAME = 0;
	}

}