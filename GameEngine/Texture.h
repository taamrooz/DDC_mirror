#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
class Texture
{
public:
	//Initializes variables
	ENGINE_API Texture(SDL_Renderer*);

	//Deallocates memory
	ENGINE_API ~Texture();

	bool loadText(std::string font, int font_size, SDL_Color color, std::string text);

	//Loads image at specified path
	bool loadFromFile(const std::string& path);

	//Deallocates texture
	ENGINE_API void free_texture();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip, double scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
	//The window renderer
	SDL_Renderer* renderer_;
};

