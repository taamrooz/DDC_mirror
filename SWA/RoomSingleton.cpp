#include "RoomSingleton.h"
#include "LevelSingleton.h"

RoomSingleton::RoomSingleton() {
	reload_room = true;
	current_room_index = 0;
	room_suffix = ".map";
	object_suffix = ".objects";
}

RoomSingleton* RoomSingleton::instance = 0;

RoomSingleton* RoomSingleton::get_instance()
{
	if (instance == nullptr) {
		instance = new RoomSingleton();
	}
	return instance;
}

std::string RoomSingleton::get_current_room_name() {
	return LevelSingleton::get_instance()->get_current_room_name_from_current_level(current_room_index);
}

void RoomSingleton::init_first_room() {
	current_room_index = 0;
}

void RoomSingleton::init_next_room() {
	current_room_index++;
}

void RoomSingleton::delete_instance()
{
	delete instance;
	instance = nullptr;
}
