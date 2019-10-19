#include "AudioSystem.h"
#include "UserInput.h"
#include "KeyBindingSingleton.h"

AudioSystem::AudioSystem(EntityManager* manager) : BaseSystem(manager) 
{}

void AudioSystem::update(double dt)
{
	for (auto i = KeyBindingSingleton::get_instance()->keys_down.begin(); i != KeyBindingSingleton::get_instance()->keys_down.end(); ++i)
	{
		if (i->first.compare("high.wav") == 0) {
			if (i->second) {
				Engine::PlayAudio("high.wav");
				i->second = false;
			}
		}

		if (i->first.compare("medium.wav") == 0) {
			if (i->second) {
				Engine::PlayAudio("medium.wav");
				i->second = false;
			}
		}

		if (i->first.compare("low.wav") == 0) {
			if (i->second) {
				Engine::PlayAudio("low.wav");
				i->second = false;
			}
		}

		if (i->first.compare("scratch.wav") == 0) {
			if (i->second) {
				Engine::PlayAudio("scratch.wav");
				i->second = false;
			}
		}
	}
}