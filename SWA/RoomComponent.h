#pragma once
#include "Component.h"
#include "Animation.h"
#include "Renderer.h"
#include <string>

struct RoomComponent : Component
{
	RoomComponent(std::string _room_name) : room_name{ _room_name } {}
	std::string room_name;
};

