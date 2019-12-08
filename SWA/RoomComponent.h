#pragma once
#include "Component.h"
#include <string>

struct RoomComponent : Component
{
	RoomComponent(std::string _room_name) : room_name{ _room_name } {}
	std::string room_name;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["RoomComponent"]["room_name"] = room_name;
	}
};

