#pragma once
#include <string>

class RoomSingleton
{
private:
	static RoomSingleton* instance;
	RoomSingleton();	
public:
	bool reload_room;
	std::string room_path;
	static RoomSingleton* get_instance();
	const int k_total_tiles_ = 192;
	const int k_tile_height_ = 80;
	const int k_tile_width_ = 80;
	const int k_level_width_ = 80;
};