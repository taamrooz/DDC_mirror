#pragma once
#include "SDL.h"
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

	//Deallocate memory
	ENGINE_API ~Texture() noexcept;

	bool load_text(std::string font, int font_size, SDL_Color color, std::string text);

	//Loads image at specified path
	bool load_from_file(std::string path);

	//Deallocate texture
	void free();

	//Set color modulation
	void set_color(uint8_t red, uint8_t green, uint8_t blue);

	//Set blending
	void set_blend_mode(SDL_BlendMode blending);

	//Set alpha modulation
	void set_alpha(uint8_t alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip, double scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0);

	//Gets image dimensions
	int get_width() const;
	int get_height() const;

private:
	//The actual hardware texture
	SDL_Texture* m_texture_;

	//Image dimensions
	int m_width_;
	int m_height_;

	//The window renderer
	SDL_Renderer* renderer_;
};

