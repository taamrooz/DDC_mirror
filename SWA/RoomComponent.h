#pragma once
#include "Component.h"
#include <string>
#include <utility>

struct RoomComponent : Component
{
public:
	RoomComponent(std::string _room_name, uint8_t _room_index) : room_name{ std::move(_room_name) }, room_index{ _room_index } {}
	std::string room_name;
	uint8_t room_index;
	RoomComponent* top{nullptr};
	RoomComponent* right{ nullptr };
	RoomComponent* down{ nullptr };
	RoomComponent* left{ nullptr };

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["RoomComponent"]["room_name"] = room_name;
		j[std::to_string(id)]["RoomComponent"]["room_index"] = room_index;
	}
};

