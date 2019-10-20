#include "KeyBindingSingleton.h"


KeyBindingSingleton::KeyBindingSingleton()
{}

/* Null, because instance will be initialized on demand. */
KeyBindingSingleton* KeyBindingSingleton::instance = 0;

KeyBindingSingleton* KeyBindingSingleton::get_instance()
{
	if (instance == 0)
	{
		//Initialization of a KeyBindingSingleton instance and filling of keybinds (Later maybe through a filereader)
		instance = new KeyBindingSingleton();
		instance->keybindings.insert(std::make_pair(SDLK_1, "high.wav"));
		instance->keybindings.insert(std::make_pair(SDLK_2, "medium.wav"));
		instance->keybindings.insert(std::make_pair(SDLK_3, "low.wav"));
		instance->keybindings.insert(std::make_pair(SDLK_4, "scratch.wav"));
		instance->keybindings.insert(std::make_pair(SDLK_w, "moveUP"));
		instance->keybindings.insert(std::make_pair(SDLK_a, "moveLeft"));
		instance->keybindings.insert(std::make_pair(SDLK_d, "moveRight"));
		instance->keybindings.insert(std::make_pair(SDLK_s, "moveDown"));
		instance->keybindings.insert(std::make_pair(SDLK_UP, "shootUp"));
		instance->keybindings.insert(std::make_pair(SDLK_LEFT, "shootLeft"));
		instance->keybindings.insert(std::make_pair(SDLK_RIGHT, "shootRight"));
		instance->keybindings.insert(std::make_pair(SDLK_DOWN, "shootDown"));

		instance->keys_down.insert(std::make_pair("high.wav", false));
		instance->keys_down.insert(std::make_pair("medium.wav", false));
		instance->keys_down.insert(std::make_pair("low.wav", false));
		instance->keys_down.insert(std::make_pair("scratch.wav", false));
		instance->keys_down.insert(std::make_pair("moveUP", false));
		instance->keys_down.insert(std::make_pair("moveLeft", false));
		instance->keys_down.insert(std::make_pair("moveRight", false));
		instance->keys_down.insert(std::make_pair("moveDown", false));
		instance->keys_down.insert(std::make_pair("shootUp", false));
		instance->keys_down.insert(std::make_pair("shootLeft", false));
		instance->keys_down.insert(std::make_pair("shootRight", false));
		instance->keys_down.insert(std::make_pair("shootDown", false));
	}

	return instance;
}