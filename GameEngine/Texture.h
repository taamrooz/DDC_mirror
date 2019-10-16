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

	ENGINE_API bool loadText(std::string font, int font_size, SDL_Color color, std::string text);

	//Loads image at specified path
	ENGINE_API bool loadFromFile(std::string path);

	//Deallocates texture
	ENGINE_API void free();

	//Set color modulation
	ENGINE_API void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	ENGINE_API void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	ENGINE_API void setAlpha(Uint8 alpha);

	//Renders texture at given point
	ENGINE_API void render(int x, int y, SDL_Rect* clip = nullptr) const;

	//Gets image dimensions
	ENGINE_API int getWidth();
	ENGINE_API int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;

	//The window renderer
	SDL_Renderer* renderer_;
};

