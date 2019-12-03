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
	bool visible;

	void ToJson(json& j, int id) override
	{
		//TODO: Daadwerkelijk opslaan van de animatie op een of andere manier (waarschijnlijk path)
		j[id]["AnimationComponent"]["flip_horizontally"] = flip_horizontally;
		j[id]["AnimationComponent"]["currentState"] = currentState;
		j[id]["AnimationComponent"]["lock_until"] = lock_until;
		j[id]["AnimationComponent"]["visible"] = visible;
	}
};