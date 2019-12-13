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
	AnimationComponent(std::unordered_map<State, std::unique_ptr<Animation>>& animations, std::unordered_map<State, std::string> state_to_path, std::unordered_map<State, int> state_to_frames) : state_to_frames{ state_to_frames }, animations { std::move(animations) }, state_to_path{ state_to_path }
	{
		currentState = State::DEFAULT;
		flip_horizontally = false;
		lock_until = 0;
	}
	std::unordered_map<State, std::string> state_to_path;
	std::unordered_map<State, int> state_to_frames;
	bool flip_horizontally;
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	State currentState;
	int lock_until;
	bool visible;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["AnimationComponent"]["flip_horizontally"] = flip_horizontally;
		j[std::to_string(id)]["AnimationComponent"]["currentState"] = currentState;
		j[std::to_string(id)]["AnimationComponent"]["visible"] = visible;

		if(state_to_path.find(State::DEFAULT) != state_to_path.end()){
			j[std::to_string(id)]["AnimationComponent"]["states"]["DEFAULT"]["path"] = state_to_path.find(State::DEFAULT)->second;
			j[std::to_string(id)]["AnimationComponent"]["states"]["DEFAULT"]["frames"] = state_to_frames.find(State::DEFAULT)->second;
			j[std::to_string(id)]["AnimationComponent"]["states"]["DEFAULT"]["scale"] = animations.find(State::DEFAULT)->second->scale;
		}
		if (state_to_path.find(State::RUN) != state_to_path.end()) {
			j[std::to_string(id)]["AnimationComponent"]["states"]["RUN"]["path"] = state_to_path.find(State::RUN)->second;
			j[std::to_string(id)]["AnimationComponent"]["states"]["RUN"]["frames"] = state_to_frames.find(State::RUN)->second;
			j[std::to_string(id)]["AnimationComponent"]["states"]["RUN"]["scale"] = animations.find(State::RUN)->second->scale;
		}
		if (state_to_path.find(State::HIT) != state_to_path.end()) {
			j[std::to_string(id)]["AnimationComponent"]["states"]["HIT"]["path"] = state_to_path.find(State::HIT)->second;
			j[std::to_string(id)]["AnimationComponent"]["states"]["HIT"]["frames"] = state_to_frames.find(State::HIT)->second;
			j[std::to_string(id)]["AnimationComponent"]["states"]["HIT"]["scale"] = animations.find(State::HIT)->second->scale;
		}
	}
};