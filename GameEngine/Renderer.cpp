#include "Renderer.h"
#include <iostream>
#include "SDL_ttf.h"
#include "Timer.h"
#include <sstream>
#include "SDL_image.h"

SDL_Window* window;
SDL_Renderer* renderer;
std::vector<SDL_Rect> rectangles;

bool Engine::init_renderer(std::string title, bool fullscreen, uint32_t width, uint32_t height) {
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

	if(TTF_Init() < 0)
	{
		std::cout << TTF_GetError() << std::endl;
		std::cout << "Unable to initialize TTF" << std::endl;
		return false;
	}
	return true;
}

Animation* Engine::load_animation(std::string path, int frames) {

	auto WALKING_ANIMATION_FRAMES = frames;
	auto gSpriteClips = std::vector<SDL_Rect>(WALKING_ANIMATION_FRAMES);
	auto texture = new Texture(renderer);
	auto animation = new Animation(WALKING_ANIMATION_FRAMES, gSpriteClips, *texture);
	texture->free();

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

void Engine::render_tile(int xpos, int ypos, int width, int height, int xclip, int yclip, Texture* texture)
{
	SDL_Rect* clip = new SDL_Rect{ xclip, yclip, width, height };
	texture->render(xpos, ypos, clip);
	delete clip;
}

bool Engine::load_sprite_sheet(std::string path, Animation* animation)
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!animation->gSpriteSheetTexture.load_from_file(path))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		int height = animation->gSpriteSheetTexture.get_height();
		int width = animation->gSpriteSheetTexture.get_width() / animation->WALKING_ANIMATION_FRAMES;
		for (int i = 0; i < animation->WALKING_ANIMATION_FRAMES; i++) {
			animation->gSpriteClips[i].x = width * i;
			animation->gSpriteClips[i].y = 0;
			animation->gSpriteClips[i].w = width;
			animation->gSpriteClips[i].h = animation->gSpriteSheetTexture.get_height();
		}
	}

	return success;
}

Texture* Engine::load_text(std::string path, uint32_t font_size, SDL_Color color, const char* text)
{
	auto* texture = new Texture(renderer);
	texture->load_text(std::move(path), font_size, color, text);
	return texture;
}

const int kFPS = 60;
const int kFPSCounterPositionOffset = 5;
const int kframeDelay = 1000 / kFPS;
uint32_t frameStart;
uint32_t frameTime;
Timer frameTimer{};
std::string timeText;
int countedFrames = 0;

int Engine::pre_update() {
	if (countedFrames > 600)
	{
		countedFrames = 0;
		frameTimer.Stop();
	}
	if (!frameTimer.IsStarted())
		frameTimer.Start();

	auto frameStart = SDL_GetTicks();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	return frameStart;
}

uint32_t Engine::get_ticks() {
	return SDL_GetTicks();
}

void Engine::render(int framestart) {
	float avgFPS = countedFrames / (frameTimer.GetTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}

	//Set text to be rendered
	timeText = "Average FPS: ";
	int avg_FPS = static_cast<int>(avgFPS);
	if(avg_FPS >= 0 && avg_FPS <= 100)
		timeText += std::to_string(avg_FPS);
	else
		timeText += std::to_string(59);

	Texture* gFPSTextTexture = Engine::load_text("manaspc.ttf", 18, { 127,255,0, 255 }, timeText.c_str());;

	//Render textures
	gFPSTextTexture->render(kFPSCounterPositionOffset, kFPSCounterPositionOffset, 
		new SDL_Rect{ 0,0,gFPSTextTexture->get_width() ,gFPSTextTexture->get_height() });
	++countedFrames;	
	
	SDL_RenderPresent(renderer);

	delete gFPSTextTexture;
	frameTime = SDL_GetTicks() - framestart;
	
	if (kframeDelay > frameTime) {
		SDL_Delay(kframeDelay - frameTime);
	}
}

void Engine::update_animation(Animation* a, double x, double y, bool flip_horizontally)
{
	const SDL_RendererFlip flip = flip_horizontally ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	a->UpdateAnimation(x, y, flip);
}

void Engine::render_texture(Texture* texture, int x, int y, SDL_Rect* clip)
{
	texture->render(x, y, clip);
}

void Engine::render_health_bar(int x, int y, bool friendly, int max_health, int current_health) {
	if (current_health <= 0) return;

	if (friendly) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	}

	// Healthbar outline
	int bar_length = 50;
	SDL_Rect* health_bar_outline = new SDL_Rect{ x, y, bar_length, 10 };
	SDL_RenderDrawRect(renderer, health_bar_outline);

	// Current health
	float health_bar_length = (float) current_health / (float) max_health * (float) bar_length;
	SDL_Rect* health_bar = new SDL_Rect{ x, y, (int) health_bar_length, 10 };
	SDL_RenderFillRect(renderer, health_bar);

	delete health_bar_outline;
	delete health_bar;
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



void Engine::add_rectangle(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	rectangles.push_back(rect);
}

void Engine::render_rectangles() 
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	for (auto const rectangle : rectangles)
	{
		SDL_RenderDrawRect(renderer, &rectangle);
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	rectangles.clear();
}