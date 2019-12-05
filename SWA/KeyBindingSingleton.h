#pragma once
#include <map>
#include <string>
#include "SDL.h"

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
	std::string get_pause_game_key() const;
	std::string get_move_up_key() const;
	std::string get_move_left_key() const;
	std::string get_move_right_key() const;
	std::string get_move_down_key() const;
	std::string get_shoot_up_key() const;
	std::string get_shoot_left_key() const;
	std::string get_shoot_right_key() const;
	std::string get_shoot_down_key() const;
	std::string get_speedhack_key() const;
	std::string get_invincible_key() const;
	std::string get_teleport_key() const;
	std::string get_next_room_key() const;
	std::string get_kill_all_key() const;
	bool is_key_down(const std::string& key);
	std::map<SDL_Keycode, std::string> keybindings;
	std::map<std::string, bool> keys_down;
	void reset_properties();
};