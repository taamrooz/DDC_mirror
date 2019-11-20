#include "AudioSystem.h"
#include "UserInput.h"
#include "KeyBindingSingleton.h"
#include "Audio.h"

AudioSystem::AudioSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager)
{}

void AudioSystem::update(double dt)
{
	for (auto& i : KeyBindingSingleton::get_instance()->keys_down)
	{
		if (i.first == "high.wav") {
			if (i.second) {
				Engine::play_audio("high.wav");
				i.second = false;
			}
		}

		if (i.first == "medium.wav") {
			if (i.second) {
				Engine::play_audio("medium.wav");
				i.second = false;
			}
		}

		if (i.first == "low.wav") {
			if (i.second) {
				Engine::play_audio("low.wav");
				i.second = false;
			}
		}

		if (i.first == "scratch.wav") {
			if (i.second) {
				Engine::play_audio("scratch.wav");
				i.second = false;
			}
		}
	}
}