#pragma once
#include <map>
#include <string>
#include "../../../../../Documents/Avans%20Hogeschool/Project%20Software%20Architectuur%20Periode%2013/SDL2-2.0.10/include/SDL_keycode.h"
class KeyBindingSingleton
{
private:
	/* Here will be the instance stored. */
	static KeyBindingSingleton* instance;

	/* Private constructor to prevent instancing. */
	KeyBindingSingleton();
public:
	/* Static access method. */
	static KeyBindingSingleton* get_instance();
	std::map<SDL_Keycode, std::string> keybindings;
	std::map<std::string, bool> keys_down;
};

