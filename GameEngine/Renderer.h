#pragma once
#include "SDL.h"
#include <string>
#include "Texture.h"
#include "Animation.h"
#include "rect2d.h"



namespace Engine {
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
	/**
	 * \brief Initializes the renderer and all of its features.
	 * @param window_title Title of the window.
	 * @param fullscreen Indicates whether or not the game is fullscreen.
	 * @param width Width of the screen.
	 * @param height Height of the screen.
	 * @return Returns true if initialization has succeeded, else false.
	 */
	ENGINE_API bool init_renderer(std::string window_title, bool fullscreen, uint16_t width, uint16_t height);
	/**
	 * \brief Updates the supplied animation with x and y positions and if the animation needs to be flipped.
	 * @param animation The pointer to the Animation that needs to be updated.
	 * @param x The X position of the Animation.
	 * @param y The Y position of the Animation.
	 * @param flip_horizontally Whether or not the Animation should be flipped horizontally.
	 */
	ENGINE_API void update_animation(Animation* animation, double x, double y, bool flip_horizontally = false);
	/**
	 * \brief Loads sprite sheet and passes it to the supplied animation.
	 * @param path The filename to the animation in the assets folder.
	 * @param animation The pointer of the animation which the sprite sheet will be set to.
	 * @return Returns true if sprite sheet could be loaded, else false.
	 */
	ENGINE_API bool load_sprite_sheet(std::string path, Animation* animation);
	/**
	 * \brief Returns a texture with a font, it's font size, the text color, and the text.
	 * @param font_path The path to the font located in the assets folder.
	 * @param font_size The font size of the text that will be loaded.
	 * @param color The color of the text.
	 * @param text The text that will be rendered.
	 * @return Returns a pointer to the created Texture.
	 */
	ENGINE_API Texture* load_text(std::string font_path, uint32_t font_size, SDL_Color color, const char* text);
	/**
	 * \brief Returns an animation by a filepath and the amount of frames the animation will have.
	 * @param path The filename to the animation in the assets folder.
	 * @param frames The amount of frames the animation has.
	 * @return Returns a pointer to the created Animation.
	 */
	ENGINE_API Animation* load_animation(std::string path, int frames);
	/**
	 * \brief Loads the tile set by specified path.
	 * @param path The path to the tileset in the assets folder.
	 * @return Returns a pointer to the created Texture.
	 */
	ENGINE_API Texture* load_tileset(std::string path);
	/**
	 * \brief Renders a tile on specific x and y position, width and height.
	 * @param xpos The X position of the tile.
	 * @param ypos The Y position of the tile.
	 * @param rectangle The clip rectangle.
	 * @param texture Pointer to the tile texture.
	 * @param scale Scale of the tile.
	 */
	ENGINE_API void render_tile(int xpos, int ypos, const rect2d& rectangle, Texture* texture, double scale = 1);
	/**
	 * \brief Renders a texture on specific x and y position with the clip of the texture.
	 * @param texture Pointer to the texture that will be rendered.
	 * @param x The X position off where it will be rendered.
	 * @param y The y position off where it will be rendered.
	 * @param clip The clip of the texture.
	 * @param scale The scale of the texture.
	 */
	ENGINE_API void render_texture(Texture* texture, int x, int y, rect2d* clip, double scale = 1);
	/**
	 * \brief Calls the draw_rectangle method on the rectangle.
	 * @param rectangle The pointer to the Rectangle.
	 */
	ENGINE_API void draw_rectangle(const rect2d& rectangle);
	/**
	 * \brief Calls the fill_rectangle method on the rectangle.
	 * @param rectangle The pointer to the Rectangle. 
	 */
	ENGINE_API void fill_rectangle(const rect2d& rectangle);
	/**
	 * \brief Adds a rectangle to the collection on specified x and y coordinates, with the width and height.
	 * @param rectangle The rect2d to be added.
	 */
	ENGINE_API void add_rectangle(rect2d* rectangle);

	/*
	 * Takes a screenshot of the current render target and saves it to a file indicated by "path"
	/**
	 * \brief Renders all rectangles in the collection.
	 */
	ENGINE_API void render_rectangles();
	/**
	 * \brief Clears the screen and returns the tick after the screen has been cleared.
	 */
	ENGINE_API int pre_update();
	/**
	* \brief Renders to the screen supplied by the tick before the textures and animations were updated.
	* @param framestart The tick.
	*/
	ENGINE_API void render(int framestart, int speed = 1);
	/**
	 * \brief Gets the number of ms after the renderer's initialization.
	 * @return milliseconds
	 */

	/*
	 * Draw the items in the inventory
	 */
	ENGINE_API void render_inventory_item(std::string path, bool selected, int x);
	ENGINE_API void render_inventory_tile(bool selected, int x);

	ENGINE_API uint32_t get_ticks();
	/**
	 * \brief Sets the renderer draw color.
	 * @param r The red value.
	 * @param g The green value.
	 * @param b The blue value.
	 * @param a The alpha value.
	 */
	ENGINE_API void set_render_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	/**
	 * \brief Takes a screenshot of the current render target and saves it as a PNG.
	 * @param width The width that will be screenshotted.
	 * @param height The height that will be screenshotted.
	 * @param xpos The X position of the screenshot, from top left.
	 * @param ypos The Y position of the screenshot, from top left.
	 * @param path The path to which the screenshot will be saved (as PNG).
	 */
	ENGINE_API void take_screenshot(int width, int height, int xpos, int ypos, const char* path);
	/**
	 * \brief Draw a line between 2 points
	 * @param x The first point x.
	 * @param y The first point y.
	 * @param x2 The second point x.
	 * @param y2 The second point y.
	 */
	ENGINE_API void render_line(int x, int y, int x2, int y2);
	/**
	 * \brief Toggles rendering the FPS counter.
	 */
	ENGINE_API void toggle_fps();
	/**
	 * \brief Destroys the renderer and all of its features.
	 */
	ENGINE_API void destroy_renderer();

};