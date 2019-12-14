#pragma once
#include "Component.h"
#include <Texture.h>
struct TextureComponent : Component {
	TextureComponent(std::unique_ptr<Texture> texture) : texture{ std::move(texture) } {}

	std::unique_ptr<Texture> texture;
	std::string path;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["TextureComponent"]["path"] = path;
	}
	
};