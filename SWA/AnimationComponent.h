#pragma once
#include "Component.h"
#include "Animation.h"
#include "Renderer.h"
#include <string>
#include <map>
enum class State {
	DEFAULT,
	RUN,
	HIT
};
struct AnimationComponent : Component
{

	AnimationComponent() = default;
	AnimationComponent(std::map<State, Animation> animations) :
		animations { animations }
	{
		currentState = State::DEFAULT;
		flip_horizontally = false;
		lock_until = 0;
	}
	bool flip_horizontally;
	std::map<State, Animation> animations;
	State currentState;
	int lock_until;
};

