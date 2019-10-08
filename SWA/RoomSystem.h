#pragma once
#include "BaseSystem.h"
#include "RoomComponent.h"

class RoomSystem :
	public BaseSystem
{
public:
	RoomSystem(EntityManager* manager, RoomComponent* room_component);
	void LoadTiles(std::string path, int total_tiles, int total_sprites, int tile_width, int level_width, int tile_height);
	void update(double dt) override;
private:
	RoomComponent* room_component;
};

