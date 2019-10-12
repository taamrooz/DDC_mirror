#pragma once
#include "Component.h"
#include <UserInput.h>

struct InputComponent : Component
{
	std::map<SDL_Keycode, std::string> keybindings;
	std::map<std::string, bool> keys_down;

	InputComponent(){
		//audio
		keybindings.insert(std::make_pair(SDLK_1, "high.wav"));
		keybindings.insert(std::make_pair(SDLK_2, "medium.wav"));
		keybindings.insert(std::make_pair(SDLK_3, "low.wav"));
		keybindings.insert(std::make_pair(SDLK_4, "scratch.wav"));

		keys_down.insert(std::make_pair("high.wav", false));
		keys_down.insert(std::make_pair("medium.wav", false));
		keys_down.insert(std::make_pair("low.wav", false));
		keys_down.insert(std::make_pair("scratch.wav", false));

		//character
		keybindings.insert(std::make_pair(SDLK_UP, "shootUp"));
		keybindings.insert(std::make_pair(SDLK_LEFT, "shootLeft"));
		keybindings.insert(std::make_pair(SDLK_RIGHT, "shootRight"));
		keybindings.insert(std::make_pair(SDLK_DOWN, "shootDown"));

		keys_down.insert(std::make_pair("shootUp", false));
		keys_down.insert(std::make_pair("shootLeft", false));
		keys_down.insert(std::make_pair("shootRight", false));
		keys_down.insert(std::make_pair("shootDown", false));


	}
	
};