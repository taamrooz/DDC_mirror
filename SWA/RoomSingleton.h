#pragma once
#include <string>

class RoomSingleton
{
private:
	static RoomSingleton* instance_;
	RoomSingleton();	
public:
	//If reload_room is true, load the map from at the room_path location
	bool reload_room;
	std::string room_name;
	static RoomSingleton* get_instance();
	std::string object_suffix;
	std::string room_suffix;
};