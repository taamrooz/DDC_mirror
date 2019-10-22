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
		animation->scale = scale;
		animation->total_frames = frames;
		flip_horizontally = false;
	}
	~AnimationComponent()
	{
		/*delete animation;*/
	}
	bool flip_horizontally;
	std::string filename;
	std::unique_ptr<Animation> animation;
	int frames{};
	int scale{};
};

