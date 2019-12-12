#pragma once
#include <string>

class RoomSingleton
{
private:
	static RoomSingleton* instance;
	RoomSingleton();	
	int current_room_index;
public:
	//If reload_room is true, load the map from at the room_path location
	bool reload_room;
	static RoomSingleton* get_instance();
	std::string get_current_room_name();
	std::string object_suffix;
	std::string room_suffix;
	void init_first_room();
	void init_next_room();
	void delete_instance();
};