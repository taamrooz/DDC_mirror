#pragma once
#include <string>
#include "SDL_mixer.h"

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine {
	/*
	 * Initializes the Audio system
	 */
	ENGINE_API bool init_audio();
	/*
	 * Finds audio based on a filename
	 */
	ENGINE_API Mix_Chunk* find_audio(std::string);
	/*
	 * Finds music based on a filename.
	 */
	ENGINE_API Mix_Music* find_music(std::string);
	/*
	 * Plays audio based on a filename.
	 */
	ENGINE_API void play_audio(std::string);
	/*
	 * Plays music based on a filename.
	 */
	ENGINE_API void play_music(std::string);
	/*
	 * Stops the music that is playing.
	 */
	ENGINE_API void stop_music();
	/*
	 * Destroys the audio system.
	 */
	ENGINE_API void close_audio();

}