#pragma once
#include "BaseSystem.h"

class RoomSystem :
	public BaseSystem
{
public:
	RoomSystem(EntityManager* manager);
	void LoadTiles(std::string path, int total_tiles, int total_sprites, int tile_width, int level_width, int tile_height);
	void update(double dt) override;
};

