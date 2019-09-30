#include "UserInput.h"

SDL_Event event;

std::pair<std::vector<SDL_Keycode>, bool> Engine::GetInputs() {
	std::vector<SDL_Keycode> stored_inputs;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			return std::make_pair(stored_inputs, false);
		}
		//Handle key press
		else if (event.type == SDL_KEYDOWN)
		{
			stored_inputs.push_back(event.key.keysym.sym);
		}
	}
	return std::make_pair(stored_inputs, true);
}
