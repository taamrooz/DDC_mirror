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
				Engine::PlayAudio("high.wav");
				i.second = false;
			}
		}

		if (i.first == "medium.wav") {
			if (i.second) {
				Engine::PlayAudio("medium.wav");
				i.second = false;
			}
		}

		if (i.first == "low.wav") {
			if (i.second) {
				Engine::PlayAudio("low.wav");
				i.second = false;
			}
		}

		if (i.first == "scratch.wav") {
			if (i.second) {
				Engine::PlayAudio("scratch.wav");
				i.second = false;
			}
		}
	}
}