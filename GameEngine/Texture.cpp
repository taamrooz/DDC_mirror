#include "Texture.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>


Texture::Texture(SDL_Renderer *renderer) : m_texture_(nullptr), m_width_(0), m_height_(0), renderer_(renderer){ }

Texture::~Texture() noexcept
{
	//Deallocate
	free();
}

bool Texture::load_text(std::string font, int font_size, SDL_Color color, std::string text)
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
	m_texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
	if(m_texture_ == nullptr)
	{
		std::cout << "Unable to create texture: " << SDL_GetError() << std::endl;
		return false;
	}
	m_height_ = surface->h;
	m_width_ = surface->w;
	TTF_CloseFont(ttf_font);
	SDL_FreeSurface(surface);
	return true;
}

bool Texture::load_from_file(std::string path)
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

			m_width_ = loadedSurface->w;
			m_height_ = loadedSurface->h;
		}

	}
	SDL_FreeSurface(loadedSurface);
	//Return success
	m_texture_ = newTexture;
	return m_texture_ != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if (m_texture_ != nullptr)
	{
		SDL_DestroyTexture(m_texture_);
		m_texture_ = nullptr;
		m_width_ = 0;
		m_height_ = 0;
	}
}

void Texture::set_color(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(m_texture_, red, green, blue);
}

void Texture::set_blend_mode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(m_texture_, blending);
}

void Texture::set_alpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(m_texture_, alpha);
}

void Texture::render(int x, int y, SDL_Rect* clip, double scale, SDL_RendererFlip flip, double angle)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_width_, m_height_ };
	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w * scale;
		renderQuad.h = clip->h * scale;
	}
	SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(m_texture_, SDL_BLENDMODE_BLEND);
	//Render to screen
	SDL_RenderCopyEx(renderer_, m_texture_, clip, &renderQuad, angle, nullptr, flip);
	
}

int Texture::get_width() const
{
	return m_width_;
}

int Texture::get_height() const
{
	return m_height_;
}
