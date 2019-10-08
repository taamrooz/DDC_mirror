#pragma once
#include "Component.h"
#include <string>

struct RoomComponent : Component
{
	RoomComponent() {
		reload_room = true;
		room_path = "lazy.map";
	};
	bool reload_room;
	std::string room_path;
};