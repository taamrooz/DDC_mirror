#pragma once
#include "Component.h"
#include <string>
struct AnimationComponent :
	public Component
{
	AnimationComponent() = default;
	AnimationComponent(std::string filename, int frames) : filename{ filename }, frames{ frames }, animation{ Engine::LoadAnimation(filename) } {
		is_active = false; 
		//animation = Engine::LoadAnimation(filename);
	}
	bool is_active;
	std::string filename;
	Animation& animation;
	int frames;
};

