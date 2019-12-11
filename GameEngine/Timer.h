#pragma once
#include "SDL_hints.h"

namespace Engine {
	#ifdef ENGINE_EXPORTS
	#define ENGINE_API __declspec(dllexport)
	#else
	#define ENGINE_API __declspec(dllimport)
	#endif
	class Timer
	{
	public:
		//Initializes variables
		ENGINE_API Timer();

		//The various clock actions
		ENGINE_API void Start();
		ENGINE_API void Stop();
		ENGINE_API void Restart();
		ENGINE_API void Pause();
		ENGINE_API void Unpause();

		//Gets the timer's time
		ENGINE_API uint32_t GetTicks();

		//Checks the status of the timer
		ENGINE_API bool IsStarted();
		ENGINE_API bool IsPaused();

	private:
		//The clock time when the timer started
		uint32_t mStartTicks;

		//The ticks stored when the timer was paused
		uint32_t mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
	};
}

