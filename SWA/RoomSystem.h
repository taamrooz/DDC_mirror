#pragma once
#include "BaseSystem.h"

class RoomSystem :
	public BaseSystem
{
public:
	RoomSystem(Engine::EntityManager<Component>* manager);
	void LoadTiles(std::string path, int total_tiles, int total_sprites, int tile_width, int level_width, int tile_height);
	void LoadObjects();
	void update(double dt) override;
private:
	//Constants for the drawing of tiles
	const int k_level_width_ = 1280;
	const int k_total_tiles_ = 300;
	const int k_tile_height_ = 64;
	const int k_tile_width_ = 64;
	const int k_total_sprites_ = 49;
	const int k_collision_tiles[37] = { 2, 3, 4, 5 ,6 ,9 ,11 ,12 , 13 ,16, 17, 18 ,19 ,20 ,23 ,24 , 25 ,26 ,27 ,30 ,31 ,32 ,33 ,34, 36 ,37 ,38 ,39 ,40, 41, 42, 43, 44, 45, 46, 47, 48};
};

