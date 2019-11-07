#include "Texture.h"
#include <SDL_ttf.h>
#include <iostream>


Texture::Texture(SDL_Renderer* renderer)
{
	//Initialize
	renderer_ = renderer;
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	//Deallocate
	free_texture();
}

bool Texture::loadText(std::string font, int font_size, SDL_Color color, std::string text)
{
	free_texture();
	const auto filename = "./assets/" + font;
	const auto ttf_font = TTF_OpenFont(filename.c_str(), font_size);
	const auto surface = TTF_RenderText_Blended(ttf_font, text.c_str(), color);
	if (surface == nullptr)
	{
		std::cout << "Unable to render text: " << TTF_GetError() << std::endl;
		return false;
	}
	mTexture = SDL_CreateTextureFromSurface(renderer_, surface);
	if (mTexture == nullptr)
	{
		std::cout << "Unable to create texture: " << SDL_GetError() << std::endl;
		return false;
	}
	mHeight = surface->h;
	mWidth = surface->w;
	TTF_CloseFont(ttf_font);
	surface->refcount++;
	SDL_FreeSurface(surface);
	
	return true;
}

bool Texture::loadFromFile(const std::string& path)
{
	//Get rid of preexisting texture
	free_texture();
	//Load image at specified path
	const auto surface = IMG_Load(("./assets/" + path).c_str());
	if (surface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", ("./assets/" + path).c_str(), IMG_GetError());
		return false;
	}
	//Color key image
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
	//Create texture from surface pixels
	mTexture = SDL_CreateTextureFromSurface(renderer_, surface);
	if (mTexture == nullptr)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", ("./assets/" + path).c_str(), SDL_GetError());
		return false;
	}
	//Get image dimensions

	mWidth = surface->w;
	mHeight = surface->h;
	surface->refcount++;
	SDL_FreeSurface(surface);
	//Return success
	return true;
}

void Texture::free_texture()
{
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}

	//mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;

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

void Texture::render(int x, int y, SDL_Rect* clip, double scale, SDL_RendererFlip flip, double angle)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w * scale;
		renderQuad.h = clip->h * scale;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer_, mTexture, clip, &renderQuad, angle, nullptr, flip);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}
