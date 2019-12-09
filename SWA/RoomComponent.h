#pragma once
#include "Component.h"
#include <string>
#include <utility>

struct RoomComponent : Component
{
public:
	RoomComponent(std::string _room_name) : room_name{std::move(_room_name)} {}
	std::string room_name;
	RoomComponent* top;
	RoomComponent* right;
	RoomComponent* down;
	RoomComponent* left;
};

