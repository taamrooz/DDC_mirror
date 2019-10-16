#include "Texture.h"
#include <SDL_ttf.h>
#include <iostream>


Texture::Texture(SDL_Renderer *renderer)
{
	//Initialize
	renderer_ = renderer;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadText(std::string font, int font_size, SDL_Color color, std::string text)
{
	free();
	const auto filename = "./assets/" + font;
	const auto ttf_font = TTF_OpenFont(filename.c_str(), font_size);
	SDL_Surface* surface = TTF_RenderText_Blended(ttf_font, text.c_str(), color);
	if(surface == nullptr)
	{
		std::cout << "Unable to render text: " << TTF_GetError() << std::endl;
		return false;
	}
	mTexture = SDL_CreateTextureFromSurface(renderer_, surface);
	if(mTexture == nullptr)
	{
		std::cout << "Unable to create texture: " << SDL_GetError() << std::endl;
		return false;
	}
	mHeight = surface->h;
	mWidth = surface->w;
	TTF_CloseFont(ttf_font);
	//SDL_FreeSurface(surface);
	return true;
}

bool Texture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(("./assets/" + path).c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", ("./assets/" + path).c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", ("./assets/" + path).c_str(), SDL_GetError());
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

void Texture::free()
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

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(int x, int y, SDL_Rect* clip, int scale, SDL_RendererFlip) const
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w * 3;
		renderQuad.h = clip->h * 3;
	}

	//Render to screen
	SDL_RenderCopy(renderer_, mTexture, clip, &renderQuad);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}
