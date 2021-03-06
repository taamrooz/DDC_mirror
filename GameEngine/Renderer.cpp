#include "Renderer.h"
#include <iostream>
#include "SDL_ttf.h"
#include "Timer.h"
#include <sstream>
#include "SDL_image.h"

SDL_Window* window;
SDL_Renderer* renderer;
std::vector<std::unique_ptr<Engine::rect2d>> rectangles;

bool Engine::init_renderer(std::string title, bool fullscreen, uint16_t width, uint16_t height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Unable to initialize SDL" << std::endl;
		return false;
	}
	auto flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if ((window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags)) == nullptr)
	{
		std::cout << "Unable to initialize Window" << std::endl;
		return false;
	}
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
	{
		std::cout << "Unable to initialize renderer" << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (!(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG))
	{
		std::cout << IMG_GetError() << std::endl;
		std::cout << "Unable to initialize Image" << std::endl;
		return false;
	}

	if (TTF_Init() < 0)
	{
		std::cout << TTF_GetError() << std::endl;
		std::cout << "Unable to initialize TTF" << std::endl;
		return false;
	}
	return true;
}

void Engine::update_animation(Animation* a, double x, double y, bool flip_horizontally)
{
	const SDL_RendererFlip flip = flip_horizontally ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	a->UpdateAnimation(x, y, flip);
}

bool Engine::load_sprite_sheet(std::string path, Animation* animation)

{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!animation->gSpriteSheetTexture->load_from_file(path))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		int height = animation->gSpriteSheetTexture->get_height();
		int width = animation->gSpriteSheetTexture->get_width() / animation->WALKING_ANIMATION_FRAMES;
		for (int i = 0; i < animation->WALKING_ANIMATION_FRAMES; i++) {
			animation->gSpriteClips[i].x(width * i);
			animation->gSpriteClips[i].y(0);
			animation->gSpriteClips[i].width(width);
			animation->gSpriteClips[i].height(animation->gSpriteSheetTexture->get_height());
		}
	}

	return success;
}

Texture* Engine::load_text(std::string font_path, uint32_t font_size, SDL_Color color, const char* text)
{
	auto texture = new Texture(renderer);
	texture->load_text(std::move(font_path), font_size, color, text);
	return texture;
}

Animation* Engine::load_animation(std::string path, int frames) {

	auto WALKING_ANIMATION_FRAMES = frames;
	auto texture = new Texture{ renderer };
	auto animation = new Animation(WALKING_ANIMATION_FRAMES, texture);
	//texture->free();

	//Load media
	if (!load_sprite_sheet(path, animation))
	{
		printf("Failed to load media!\n");
	}

	return animation;
}

Texture* Engine::load_tileset(std::string path)
{
	Texture* texture = new Texture(renderer);
	texture->load_from_file(path);
	return texture;
}

void Engine::render_tile(int xpos, int ypos, const rect2d& rectangle, Texture* texture, double scale)
{
	texture->render(xpos, ypos, &rectangle, scale);
}

void Engine::render_texture(Texture* texture, int x, int y, rect2d* clip, double scale)
{
	texture->render(x, y, clip, scale);
}

void Engine::draw_rectangle(const rect2d& rectangle)
{
	SDL_RenderDrawRect(renderer, rectangle.unwrap());
}

void Engine::fill_rectangle(const rect2d& rectangle)
{
	SDL_RenderFillRect(renderer, rectangle.unwrap());
}

void Engine::add_rectangle(rect2d* rectangle)
{
	rectangles.push_back(std::unique_ptr<rect2d>(rectangle));
}

void Engine::render_rectangles()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	for (auto &rectangle : rectangles)
	{
		SDL_RenderDrawRect(renderer, rectangle->unwrap());
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	rectangles.clear();
}

const int kFPS = 60;
const int kFPSCounterPositionOffset = 5;
const int kframeDelay = 1000 / kFPS;
uint32_t frameStart;
uint32_t frameTime;
Engine::Timer frameTimer{};
std::string timeText;
int countedFrames = 0;
bool render_fps = true;

int Engine::pre_update() {
	if (countedFrames > 600)
	{
		countedFrames = 0;
		frameTimer.Stop();
	}
	if (!frameTimer.IsStarted())
		frameTimer.Start();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	auto frameStart = SDL_GetTicks();
	return frameStart;
}

void Engine::toggle_fps()
{
	render_fps = !render_fps;
}

void Engine::render(int framestart, int speed) {
	float avgFPS = countedFrames / (frameTimer.GetTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}

	//Set text to be rendered
	timeText = "Average FPS: ";
	int avg_FPS = static_cast<int>(avgFPS);
	if (avg_FPS >= 0 && avg_FPS <= 100)
		timeText += std::to_string(avg_FPS);
	else
		timeText += std::to_string(59);

	Texture* gFPSTextTexture = load_text("manaspc.ttf", 18, { 127,255,0, 255 }, timeText.c_str());;

	//Render textures
	if (render_fps) {
		int w;
		SDL_GL_GetDrawableSize(window, &w, nullptr);
		auto rec = rect2d{ 0,0,gFPSTextTexture->get_width() ,gFPSTextTexture->get_height() };
		gFPSTextTexture->render(w - gFPSTextTexture->get_width() - kFPSCounterPositionOffset, 0 + kFPSCounterPositionOffset,
			&rec);
	}
	++countedFrames;

	SDL_RenderPresent(renderer);

	delete gFPSTextTexture;
	frameTime = SDL_GetTicks() - framestart;
	int frameDelay = kframeDelay / speed;

	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
}

uint32_t Engine::get_ticks() {
	return SDL_GetTicks();
}

void Engine::set_render_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Engine::destroy_renderer() {
	rectangles.clear();
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Engine::take_screenshot(int width, int height, int xpos, int ypos, const char* path)
{
	SDL_Surface* sshot = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_Rect rect{ xpos, ypos, width, height };
	SDL_RenderReadPixels(renderer, &rect, sshot->format->format, sshot->pixels, sshot->pitch);
	IMG_SavePNG(sshot, path);
	SDL_FreeSurface(sshot);
}

void Engine::render_line(int x, int y, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x, y, x2, y2);
}

int Engine::get_window_height() {
	return SDL_GetWindowSurface(window)->h;
}
