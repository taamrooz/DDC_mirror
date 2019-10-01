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

	ENGINE_API std::pair<std::vector<SDL_Keycode>, bool> GetInputs();

}