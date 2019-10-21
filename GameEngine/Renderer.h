#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Texture.h"
#include "Animation.h"


#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine {
	/*
	 * Initializes the renderer and all of its features.
	 */
	ENGINE_API bool InitRenderer(std::string, bool, Uint32, Uint32);
	/*
	 * Updates the supplied animation with x and y positions and if the animation needs to be flipped.
	 */
	ENGINE_API void UpdateAnimation(Animation* a, double, double, bool flip_horizontally = false);
	/*
	 * Loads sprite sheet and passes it to the supplied animation.
	 */
	ENGINE_API bool LoadSpriteSheet(std::string path, Animation*);
	/*
	 * Returns a texture with a font, it's font size, the text color, and the text.
	 */
	ENGINE_API Texture* LoadText(std::string path, uint32_t font_size, SDL_Color color, const char* text);
	/*
	 * Returns an animation by a filepath and the amount of frames the animation will have.
	 */
	ENGINE_API Animation& LoadAnimation(std::string path, int frames);
	/*
	 * Loads the tile set by specified path.
	 */
	ENGINE_API Texture* LoadTileset(std::string path);
	/*
	 * Renders a tile on specific x and y position, width and height.
	 */
	ENGINE_API void RenderTile(int xpos, int ypos, int width, int height, int xclip, int yclip, Texture* texture);
	/*
	 * Renders a texture on specific x and y position with the clip of the texture.
	 */
	ENGINE_API void RenderTexture(Texture* texture, int x, int y, SDL_Rect* clip);
	/*
	 * Destroys the renderer and all of its features.
	 */
	ENGINE_API void DestroyRenderer();
	/*
	 * Renders to the screen supplied by the tick before the textures and animations were updated.
	 */
	ENGINE_API void Render(int framestart);
	/*
	 * Clears the screen and returns the tick after the screen has been cleared.
	 */
	ENGINE_API int PreUpdate();
	/*
	 * Adds a rectangle to the collection on specified x and y coordinates, with the width and height.
	 */
	ENGINE_API void AddRectangle(int x, int y, int w, int h);
	/*
	 * Renders all rectangles in the collection.
	 */
	ENGINE_API void RenderRectangles();
	ENGINE_API Uint32 GetTicks();
}