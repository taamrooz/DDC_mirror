#pragma once
#include <string>
#include <SDL_mixer.h>
#include <map>

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine {

	ENGINE_API bool InitAudio();
	ENGINE_API Mix_Chunk* FindAudio(std::string);
	ENGINE_API Mix_Music* FindMusic(std::string);
	ENGINE_API void PlayAudio(std::string);
	ENGINE_API void PlayMusic(std::string);
	ENGINE_API void StopMusic();
	ENGINE_API void CloseAudio();

}