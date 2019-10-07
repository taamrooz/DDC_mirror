#include "Renderer.h"
#include <iostream>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surf;

//std::vector<Animation*> animations;

//int frames, std::string path, SDL_Window* window, SDL_Renderer* renderer
bool Engine::InitRenderer(std::string title, bool fullscreen, Uint32 width, Uint32 height) {
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
	surf = SDL_GetWindowSurface(window);
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
	return true;
}

Animation& Engine::LoadAnimation(std::string path, int frames) {

	auto WALKING_ANIMATION_FRAMES = frames;
	auto gSpriteClips = std::vector<SDL_Rect>(WALKING_ANIMATION_FRAMES);
	auto texture = new Texture(renderer);
	auto animation = new Animation(WALKING_ANIMATION_FRAMES, gSpriteClips, *texture);
	texture->free();
	//animations.push_back(animation.get());

	//Load media
	if (!Engine::LoadSpriteSheet(path, animation))
	{
		printf("Failed to load media!\n");
	}

	return *animation;
}

void Engine::LoadTiles(std::string path, int total_tiles, int total_sprites, int tile_width, int level_width, int tile_height)
{
	//Success flag
	bool tilesLoaded = true;
	
	//tiles vector
	std::vector<std::vector<int>> tiles;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map(path);

	//If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < total_tiles; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < total_sprites))
			{
				tiles[i][0] = x;
				tiles[i][1] = y;
				tiles[i][2] = tileType;
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += tile_width;

			//If we've gone too far
			if (x >= level_width)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += tile_height;
			}
		}
	}

	//Close the file
	map.close();


	//If the map was loaded fine
	//return tilesLoaded;
}

Texture* Engine::LoadTileset(std::string path)
{
	Texture* texture = new Texture(renderer);
	texture->loadFromFile(path);
	return texture;
}

void Engine::RenderTile(int xpos, int ypos, int width, int height, int tiletype, Texture* texture)
{
	SDL_Rect* clip = new SDL_Rect{ xpos, ypos, width, height };
	texture->render(xpos, ypos, clip);
	clip = nullptr;
}

bool Engine::LoadSpriteSheet(std::string path, Animation* animation)
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!animation->gSpriteSheetTexture.loadFromFile(path))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		int height = animation->gSpriteSheetTexture.getHeight();
		int width = animation->gSpriteSheetTexture.getWidth() / animation->WALKING_ANIMATION_FRAMES;
		for (int i = 0; i < animation->WALKING_ANIMATION_FRAMES; i++) {
			animation->gSpriteClips[i].x = width * i;
			animation->gSpriteClips[i].y = 0;
			animation->gSpriteClips[i].w = width;
			animation->gSpriteClips[i].h = animation->gSpriteSheetTexture.getHeight();
		}
	}

	return success;
}


const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

void Engine::RenderClear() {
	SDL_RenderClear(renderer);
}

void Engine::Render() {
	SDL_UpdateWindowSurface(window);
	SDL_RenderPresent(renderer);
	
	frameStart = SDL_GetTicks();
	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
}

void Engine::UpdateAnimation(Animation* a)
{
	a->UpdateAnimation();	
}

void Engine::DestroyRenderer() {
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	IMG_Quit();
	SDL_Quit();
}