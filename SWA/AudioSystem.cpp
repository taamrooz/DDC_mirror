#include "AudioSystem.h"
#include "UserInput.h"

AudioSystem::AudioSystem(EntityManager* manager, InputComponent* inputcomponent) : BaseSystem(manager) {
	input_component = inputcomponent;
}

void AudioSystem::update(double dt)
{
	for (auto i = input_component->keys_down.begin(); i != input_component->keys_down.end(); ++i)
	{		
		if (i->second) {
			std::cout << i->second << std::endl;
			if (!i->first.compare("stop_music"))
				Engine::StopMusic();
			else
				Engine::PlayAudio(i->first);
			//i->second = false;
		}
	}
}