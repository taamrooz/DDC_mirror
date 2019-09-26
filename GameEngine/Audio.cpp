#include "Audio.h"

bool InitAudio() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	return true;
}

void PlayAudio(std::string filename) {
	Mix_PlayChannel(0, FindAudio("./assets/" + filename), 0);
}

void PlayMusic(std::string filename) {
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(FindMusic(filename), 0);
	}
	//If music is being played
	else
	{
		//If the music is paused
		if (Mix_PausedMusic() == 1)
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
}

void StopMusic() {
	Mix_HaltMusic();
}

Mix_Chunk* FindAudio(std::string filename) {
	auto sound_effect = Mix_LoadWAV(filename.c_str());
	if (sound_effect == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	return sound_effect;
}

Mix_Music* FindMusic(std::string filename) {
	auto music = Mix_LoadMUS(filename.c_str());
	if (music == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	return music;
}