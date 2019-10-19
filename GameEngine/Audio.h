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
	/*
	 * Initializes the Audio system
	 */
	ENGINE_API bool InitAudio();
	/*
	 * Finds audio based on a filename
	 */
	ENGINE_API Mix_Chunk* FindAudio(std::string);
	/*
	 * Finds music based on a filename.
	 */
	ENGINE_API Mix_Music* FindMusic(std::string);
	/*
	 * Plays audio based on a filename.
	 */
	ENGINE_API void PlayAudio(std::string);
	/*
	 * Plays music based on a filename.
	 */
	ENGINE_API void PlayMusic(std::string);
	/*
	 * Stops the music that is playing.
	 */
	ENGINE_API void StopMusic();
	/*
	 * Destroys the audio system.
	 */
	ENGINE_API void CloseAudio();

}