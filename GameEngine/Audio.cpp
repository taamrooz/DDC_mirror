#include "Audio.h"
#include <map>

std::map<std::string, Mix_Chunk*> sound_effects;
std::map<std::string, Mix_Music*> music;

bool Engine::init_audio() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	Mix_Volume(-1, 5);
	Mix_VolumeMusic(5);
	return true;
}

void Engine::play_audio(const std::string filename) {
	const auto exists = sound_effects.find(filename);
	if (exists != sound_effects.end()) {
		Mix_PlayChannel(-1, sound_effects[filename], 0);
	}
	else {
		const auto audiofile = find_audio("./assets/" + filename);
		Mix_PlayChannel(-1, audiofile, 0);
		sound_effects.emplace(filename, audiofile);
	}
}

void Engine::play_music(const std::string filename) {
	//Play music
	if (Mix_PlayingMusic() == 0)
	{
		const auto exists = music.find(filename);
		if (exists != music.end()) {
			Mix_PlayMusic(music[filename], 1);
		}
		else {
			const auto audiofile = find_music("./assets/" + filename);
			Mix_PlayMusic(audiofile, -1);
			music.emplace(filename, audiofile);
		}
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

void Engine::stop_music() {
	Mix_HaltMusic();
}

Mix_Chunk* Engine::find_audio(const std::string filename) {
	const auto sound_effect = Mix_LoadWAV(filename.c_str());
	if (sound_effect == nullptr)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	return sound_effect;
}

Mix_Music* Engine::find_music(const std::string filename) {
	const auto music = Mix_LoadMUS(filename.c_str());
	if (music == nullptr)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	return music;
}

void Engine::close_audio() {
	for (auto i = sound_effects.begin(); i != sound_effects.end(); ++i)
	{
		Mix_FreeChunk(i->second);
	}
	for (auto i = music.begin(); i != music.end(); ++i)
	{
		Mix_FreeMusic(i->second);
	}
	Mix_Quit();
}