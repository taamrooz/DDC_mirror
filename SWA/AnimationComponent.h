#pragma once
#include "Component.h"
#include "Animation.h"
#include <utility>

enum class State {
	DEFAULT,
	RUN,
	HIT
};
struct AnimationComponent : Component
{

	AnimationComponent() = default;
	AnimationComponent(std::unordered_map<State, std::unique_ptr<Animation>>& animations): animations {std::move(animations)}
	{
		currentState = State::DEFAULT;
		flip_horizontally = false;
		lock_until = 0;
	}
	bool flip_horizontally;
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	State currentState;
	int lock_until;
};

