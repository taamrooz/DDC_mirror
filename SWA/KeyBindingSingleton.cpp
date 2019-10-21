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
		instance->keys_down.insert(std::make_pair(instance->get_move_up_key_binding(), false));
		instance->keys_down.insert(std::make_pair(instance->get_move_left_key_binding() , false));
		instance->keys_down.insert(std::make_pair(instance->get_move_right_key_binding(), false));
		instance->keys_down.insert(std::make_pair(instance->get_move_down_key_binding(), false));
		instance->keys_down.insert(std::make_pair(instance->get_shoot_up_key_binding(), false));
		instance->keys_down.insert(std::make_pair(instance->get_shoot_left_key_binding(), false));
		instance->keys_down.insert(std::make_pair(instance->get_shoot_right_key_binding(), false));
		instance->keys_down.insert(std::make_pair(instance->get_shoot_down_key_binding(), false));
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

std::string KeyBindingSingleton::get_shoot_up_key_binding() {
	return "shootUp";
}

std::string KeyBindingSingleton::get_shoot_left_key_binding() {
	return "shootLeft";
}

std::string KeyBindingSingleton::get_shoot_right_key_binding() {
	return "shootRight";
}

std::string KeyBindingSingleton::get_shoot_down_key_binding() {
	return "shootDown";
}