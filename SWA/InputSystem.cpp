#include "InputSystem.h"
#include "UserInput.h"
#include "KeyBindingSingleton.h"
#include "Audio.h"

InputSystem::InputSystem(Engine::EntityManager<Component>* manager, Core &core) : BaseSystem(manager) {
	core_ = &core;
}

void InputSystem::update(double dt)
{
	//Constants that define location of elements in the tuple that gets returned by Engine::GetInputs()
	const int k_keydown = 0;
	const int k_keyup = 1;
	const int k_stop = 2;

	auto inputs = Engine::GetInputs();

	//Quit if user wants to exit
	if (!std::get<k_stop>(inputs)) {
		core_->StopGameLoop();
		return;
	}
	
	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_q)
		{
			Engine::stop_music();
			core_->scene_manager_->set_scene("mainmenu");
			Engine::play_music("mainmenu.wav");
			break;
		}
		if (KeyBindingSingleton::get_instance()->keybindings.find(keycode) != KeyBindingSingleton::get_instance()->keybindings.end()) {
			auto command = KeyBindingSingleton::get_instance()->keybindings.at(keycode);
			KeyBindingSingleton::get_instance()->keys_down.at(command) = true;

			if (command == KeyBindingSingleton::get_instance()->get_pause_game_key()) {
				core_->toggle_pause();
			}
		}
	}

	//Handle all key up events
	for (const auto& keycode : std::get<k_keyup>(inputs))
	{
		if (KeyBindingSingleton::get_instance()->keybindings.find(keycode) != KeyBindingSingleton::get_instance()->keybindings.end()) {
			auto command = KeyBindingSingleton::get_instance()->keybindings.at(keycode);
			KeyBindingSingleton::get_instance()->keys_down.at(command) = false;
		}
	}
}