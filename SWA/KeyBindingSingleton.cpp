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
		instance->keybindings.insert(std::make_pair(SDLK_UP, "moveUP"));
		instance->keybindings.insert(std::make_pair(SDLK_LEFT, "moveLeft"));
		instance->keybindings.insert(std::make_pair(SDLK_RIGHT, "moveRight"));
		instance->keybindings.insert(std::make_pair(SDLK_DOWN, "moveDown"));

		instance->keys_down.insert(std::make_pair("high.wav", false));
		instance->keys_down.insert(std::make_pair("medium.wav", false));
		instance->keys_down.insert(std::make_pair("low.wav", false));
		instance->keys_down.insert(std::make_pair("scratch.wav", false));
		instance->keys_down.insert(std::make_pair(instance->get_move_up_key_binding(), false));
		instance->keys_down.insert(std::make_pair(instance->get_move_left_key_binding() , false));
		instance->keys_down.insert(std::make_pair(instance->get_move_right_key_binding(), false));
		instance->keys_down.insert(std::make_pair(instance->get_move_down_key_binding(), false));
	}

	return instance;
}

std::string KeyBindingSingleton::get_move_up_key_binding() {
	return "moveUP";
}

std::string KeyBindingSingleton::get_move_left_key_binding() {
	return "moveLeft";
}

std::string KeyBindingSingleton::get_move_right_key_binding() {
	return "moveRight";
}

std::string KeyBindingSingleton::get_move_down_key_binding() {
	return "moveDown";
}