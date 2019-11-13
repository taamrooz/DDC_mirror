#include "RoomSingleton.h"

RoomSingleton::RoomSingleton() {
	reload_room = true;
	room_name = "leveleditor";
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
