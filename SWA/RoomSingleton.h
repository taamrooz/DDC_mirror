#pragma once
#include <string>

class RoomSingleton
{
private:
	static RoomSingleton* instance;
	RoomSingleton();	
public:
	//If reload_room is true, load the map from at the room_path location
	bool reload_room;
	std::string room_path;

	static RoomSingleton* get_instance();
};