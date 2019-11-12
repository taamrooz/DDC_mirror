#pragma once
#include <map>
#include <string>
#include <SDL.h>

class KeyBindingSingleton
{
private:
	/* The instance will be stored here. */
	static KeyBindingSingleton* instance;

	/* Private constructor to prevent instancing. */
	KeyBindingSingleton();
public:
	/* Static access method. */
	static KeyBindingSingleton* get_instance();
	std::string get_move_up_key_binding();
	std::string get_move_left_key_binding();
	std::string get_move_right_key_binding();
	std::string get_move_down_key_binding();
	std::string get_shoot_up_key_binding();
	std::string get_shoot_left_key_binding();
	std::string get_shoot_right_key_binding();
	std::string get_shoot_down_key_binding();
	std::string get_move_up_key();
	std::string get_move_left_key();
	std::string get_move_right_key();
	std::string get_move_down_key();
	std::string get_shoot_up_key();
	std::string get_shoot_left_key();
	std::string get_shoot_right_key();
	std::string get_shoot_down_key();
	std::map<SDL_Keycode, std::string> keybindings;
	std::map<std::string, bool> keys_down;
};