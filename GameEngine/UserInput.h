#pragma once
#include <string>
#include <SDL.h>
#include <map>
#include <vector>

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine {
	/*
	 * Returns a tuple of a vector which contains the keys that were pressed, a vector which contains the keys that were released, and if the user is still continuing by not having pressed the quit button.
	 */
	ENGINE_API std::tuple<std::vector<SDL_Keycode>, std::vector<SDL_Keycode>, bool, std::string> GetInputs();
	
	ENGINE_API std::pair<int, int> GetMouseState();

	ENGINE_API void StartTextInput();

	ENGINE_API void StopTextInput();
}