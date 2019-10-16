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
	std::map<SDL_Keycode, std::string> keybindings;
	std::map<std::string, bool> keys_down;
};