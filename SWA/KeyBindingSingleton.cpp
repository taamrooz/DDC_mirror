#include "KeyBindingSingleton.h"


KeyBindingSingleton::KeyBindingSingleton()
{}

/* Null, because instance will be initialized on demand. */
KeyBindingSingleton* KeyBindingSingleton::instance = nullptr;

KeyBindingSingleton* KeyBindingSingleton::get_instance()
{
	if (instance == nullptr)
	{
		//Initialization of a KeyBindingSingleton instance and filling of keybinds (Later maybe through a filereader)
		instance = new KeyBindingSingleton();
		instance->keybindings.insert(std::make_pair(SDLK_1, "1"));
		instance->keybindings.insert(std::make_pair(SDLK_2, "2"));
		instance->keybindings.insert(std::make_pair(SDLK_3, "3"));
		instance->keybindings.insert(std::make_pair(SDLK_4, "4"));
		instance->keybindings.insert(std::make_pair(SDLK_5, "5"));
		instance->keybindings.insert(std::make_pair(SDLK_6, "6"));
		instance->keybindings.insert(std::make_pair(SDLK_7, "7"));
		instance->keybindings.insert(std::make_pair(SDLK_8, "8"));
		instance->keybindings.insert(std::make_pair(SDLK_9, "9"));
		instance->keybindings.insert(std::make_pair(SDLK_0, "10"));


		instance->keybindings.insert(std::make_pair(SDLK_p, instance->get_pause_game_key()));
		instance->keybindings.insert(std::make_pair(SDLK_w, instance->get_move_up_key()));
		instance->keybindings.insert(std::make_pair(SDLK_a, instance->get_move_left_key()));
		instance->keybindings.insert(std::make_pair(SDLK_d, instance->get_move_right_key()));
		instance->keybindings.insert(std::make_pair(SDLK_s, instance->get_move_down_key()));
		instance->keybindings.insert(std::make_pair(SDLK_UP, instance->get_shoot_up_key()));
		instance->keybindings.insert(std::make_pair(SDLK_LEFT, instance->get_shoot_left_key()));
		instance->keybindings.insert(std::make_pair(SDLK_RIGHT, instance->get_shoot_right_key()));
		instance->keybindings.insert(std::make_pair(SDLK_DOWN, instance->get_shoot_down_key()));
		instance->keybindings.insert(std::make_pair(SDLK_INSERT, instance->get_speedhack_key()));
		instance->keybindings.insert(std::make_pair(SDLK_h, instance->get_invincible_key()));
		instance->keybindings.insert(std::make_pair(SDLK_t, instance->get_teleport_key()));
		instance->keybindings.insert(std::make_pair(SDLK_n, instance->get_next_room_key()));
		instance->keybindings.insert(std::make_pair(SDLK_k, instance->get_kill_all_key()));
		instance->keybindings.insert(std::make_pair(SDLK_PAGEUP, instance->get_gamespeed_increase()));
		instance->keybindings.insert(std::make_pair(SDLK_PAGEDOWN, instance->get_gamespeed_decrease()));

		instance->keys_down.insert(std::make_pair(instance->get_pause_game_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_move_up_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_move_left_key() , false));
		instance->keys_down.insert(std::make_pair(instance->get_move_right_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_move_down_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_shoot_up_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_shoot_left_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_shoot_right_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_shoot_down_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_speedhack_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_invincible_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_teleport_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_next_room_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_kill_all_key(), false));
		instance->keys_down.insert(std::make_pair(instance->get_gamespeed_increase(), false));
		instance->keys_down.insert(std::make_pair(instance->get_gamespeed_decrease(), false));

		instance->keys_down.insert(std::make_pair("1", false));
		instance->keys_down.insert(std::make_pair("2", false));
		instance->keys_down.insert(std::make_pair("3", false));
		instance->keys_down.insert(std::make_pair("4", false));
		instance->keys_down.insert(std::make_pair("5", false));
		instance->keys_down.insert(std::make_pair("6", false));
		instance->keys_down.insert(std::make_pair("7", false));
		instance->keys_down.insert(std::make_pair("8", false));
		instance->keys_down.insert(std::make_pair("9", false));
		instance->keys_down.insert(std::make_pair("10", false));
	}

	return instance;
}

std::string KeyBindingSingleton::get_pause_game_key() const {
	return "p";
}

std::string KeyBindingSingleton::get_move_up_key() const {
	return "W";
}

std::string KeyBindingSingleton::get_move_left_key() const {
	return "A";
}

std::string KeyBindingSingleton::get_move_right_key() const {
	return "D";
}

std::string KeyBindingSingleton::get_move_down_key() const {
	return "S";
}

std::string KeyBindingSingleton::get_shoot_up_key() const {
	return "^";
}

std::string KeyBindingSingleton::get_shoot_left_key() const {
	return "<";
}

std::string KeyBindingSingleton::get_shoot_right_key() const {
	return ">";
}

std::string KeyBindingSingleton::get_shoot_down_key() const {
	return "`";
}

std::string KeyBindingSingleton::get_speedhack_key() const
{
	return "insert";
}

std::string KeyBindingSingleton::get_invincible_key() const
{
	return "H";
}

std::string KeyBindingSingleton::get_teleport_key() const
{
	return "T";
}

std::string KeyBindingSingleton::get_next_room_key() const
{
	return "N";
}

std::string KeyBindingSingleton::get_kill_all_key() const
{
	return "K";
}

std::string KeyBindingSingleton::get_gamespeed_increase() const
{
	return "pageUP";
}

std::string KeyBindingSingleton::get_gamespeed_decrease() const
{
	return "pageDOWN";
}

bool KeyBindingSingleton::is_key_down(const std::string& key)
{
	if (keys_down.find(key) == keys_down.end()) return false;
	return keys_down.find(key)->second;
}

void KeyBindingSingleton::reset_properties() {
	for (auto& key_down : get_instance()->keys_down) {
		key_down.second = false;
	}
}
