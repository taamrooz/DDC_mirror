#pragma once
#include "BaseSystem.h"

class RoomSystem :
	public BaseSystem
{
public:
	RoomSystem(EntityManager* manager);
	void LoadTiles(std::string path, int total_tiles, int total_sprites, int tile_width, int level_width, int tile_height);
	void update(double dt) override;
private:
	//Constants for the drawing of tiles
	const int k_level_width_ = 1280;
	const int k_total_tiles_ = 192;
	const int k_tile_height_ = 80;
	const int k_tile_width_ = 80;
	const int k_total_sprites_ = 12;
};

