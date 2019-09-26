#pragma once
#include <string>
#include <SDL_mixer.h>

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

extern "C" ENGINE_API bool InitAudio();
extern "C" ENGINE_API Mix_Chunk* FindAudio(std::string path);
extern "C" ENGINE_API Mix_Music* FindMusic(std::string path);
extern "C" ENGINE_API void PlayAudio(std::string path);
extern "C" ENGINE_API void PlayMusic(std::string path);
extern "C" ENGINE_API void StopMusic();

