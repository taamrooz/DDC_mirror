#include "RoomSingleton.h"

RoomSingleton::RoomSingleton() {
	reload_room = true;
	room_name = "lazy";
	room_suffix = ".map";
	object_suffix = ".objects";
}

RoomSingleton* RoomSingleton::instance_ = nullptr;

RoomSingleton* RoomSingleton::get_instance()
{
	if (instance_ == nullptr) {
		instance_ = new RoomSingleton();
	}
	return instance_;
}
