#pragma once
#include "Component.h"
#include "Animation.h"
#include "Renderer.h"
#include <string>
struct AnimationComponent : Component
{
	AnimationComponent() = default;
	AnimationComponent(const std::string& filename, const int frames) : filename{ filename }, animation{ Engine::LoadAnimation(filename, frames) }, frames{ frames } {
		is_active = false; 
		//animation = Engine::LoadAnimation(filename);
	}
	bool is_active{};
	std::string filename;
	Animation& animation;
	int frames{};
};

