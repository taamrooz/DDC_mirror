#include "TextureRenderer.h"



void loadTexture(std::string path, SDL_Window* window, int x, int y, int width, int height) {
	SDL_Texture* gTexture = NULL;
	SDL_Renderer* gRenderer = SDL_GetRenderer(window);
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
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		//SDL_FreeSurface(loadedSurface);
	}
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	SDL_RenderCopy(gRenderer, newTexture, NULL, &rect);
}