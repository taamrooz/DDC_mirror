#include "UserInput.h"

SDL_Event event;

std::tuple<std::vector<SDL_Keycode>, std::vector<SDL_Keycode>, bool> Engine::GetInputs() {
	std::vector<SDL_Keycode> keysdown;
	std::vector<SDL_Keycode> keysup;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			return std::make_tuple(keysdown, keysup, false);
		}
		//Handle key press
		else if (event.type == SDL_KEYDOWN)
		{
			keysdown.push_back(event.key.keysym.sym);
		}
		//Handle key up
		else if (event.type == SDL_KEYUP)
		{
			keysup.push_back(event.key.keysym.sym);
		}
	}
	return std::make_tuple(keysdown, keysup, true);
}
