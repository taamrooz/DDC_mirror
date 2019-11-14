#include "RoomSingleton.h"

RoomSingleton::RoomSingleton() {
	reload_room = true;
	current_room_index = 0;
	room_suffix = ".map";
	object_suffix = ".objects";
}

RoomSingleton* RoomSingleton::instance = 0;

RoomSingleton* RoomSingleton::get_instance()
{
	if (instance == 0) {
		instance = new RoomSingleton();
	}
	return instance;
}

std::string RoomSingleton::get_current_room_name() {
	return room_names[current_room_index];
}
