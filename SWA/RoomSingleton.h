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
	bool reload_level;
	int current_room_index;
	std::string room_names[3] = { "lazy", "second", "third" };
	static RoomSingleton* get_instance();
	std::string get_current_room_name();
	std::string object_suffix;
	std::string room_suffix;
};