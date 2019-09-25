#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

class AnimationFacade {
public:
	AnimationFacade(int frames, std::string path, SDL_Window* window, SDL_Renderer* gRenderer);
	void updateAnimation();
	bool loadMedia(std::string path);
	int CURRENT_FRAME = 0;

	int WALKING_ANIMATION_FRAMES;
	std::vector<SDL_Rect> gSpriteClips;
	LTexture gSpriteSheetTexture;
};