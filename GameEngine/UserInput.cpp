#include "UserInput.h"

SDL_Event event;

std::tuple<std::vector<SDL_Keycode>, std::vector<SDL_Keycode>, bool, std::string> Engine::GetInputs() {
	std::vector<SDL_Keycode> keysdown;
	std::vector<SDL_Keycode> keysup;
	std::string text;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			return std::make_tuple(keysdown, keysup, false, "");
		}
		if (SDL_IsTextInputActive())
		{
			//Special text input event
			if (event.type == SDL_TEXTINPUT)
			{
				//Append character
				text.append(event.text.text);
			}
		}
		//Handle key press
		if (event.type == SDL_KEYDOWN)
		{
			keysdown.push_back(event.key.keysym.sym);
		}
		//Handle key up
		else if (event.type == SDL_KEYUP)
		{
			keysup.push_back(event.key.keysym.sym);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			keysdown.push_back(event.button.button);
		}
	}
	return std::make_tuple(keysdown, keysup, true, text);
}

//Returns the X and Y positions of the mouse in a pair
std::pair<int, int> Engine::GetMouseState()
{
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y);
	return std::make_pair(x, y);
};

void Engine::StartTextInput()
{
	SDL_StartTextInput();
}

void Engine::StopTextInput()
{
	SDL_StopTextInput();
}