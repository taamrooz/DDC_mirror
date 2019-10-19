#pragma once
#include "Component.h"
#include "Animation.h"
#include "Renderer.h"
#include <string>
struct AnimationComponent : Component
{
	AnimationComponent() = default;
	AnimationComponent(const std::string& filename, const int frames, const int scale) : 
		filename{ filename }, 
		animation{ Engine::LoadAnimation(filename, frames) }
	{
		animation.scale = scale;
		animation.total_frames = frames;
		flip_horizontally = false;
		flip_vertically = false;
	}
	std::string filename;
	Animation& animation;
	bool flip_horizontally;
	bool flip_vertically;
	int frames{};
	int scale{};
};

