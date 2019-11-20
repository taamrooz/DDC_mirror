#pragma once
#include "Component.h"
#include <Texture.h>
struct TextureComponent : Component {
	TextureComponent(std::string path) : path{ path } {}

	std::string path;
};