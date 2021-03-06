#pragma once
#include "Component.h"
struct TileComponent : Component
{
	TileComponent(const int x_pos, const int y_pos, const int width, const int height, const int tiletype)
		: x_pos{ x_pos }, y_pos{ y_pos }, width{ width }, height{ height }, tiletype{ tiletype } {}

	int x_pos;
	int y_pos;
	int width;
	int height;
	int tiletype;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["TileComponent"]["x_pos"] = x_pos;
		j[std::to_string(id)]["TileComponent"]["y_pos"] = y_pos;
		j[std::to_string(id)]["TileComponent"]["width"] = width;
		j[std::to_string(id)]["TileComponent"]["height"] = height;
		j[std::to_string(id)]["TileComponent"]["tiletype"] = tiletype;
	}
};

