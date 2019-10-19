#include "InputSystem.h"
#include "UserInput.h"
#include "KeyBindingSingleton.h"

InputSystem::InputSystem(EntityManager* manager, Core &core) : BaseSystem(manager) {
	InputSystem::core = &core;
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
		core->StopGameLoop();
		return;
	}
	
	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_q)
		{
			core->scene_manager_->pop_scene();
			break;
		}
		if (KeyBindingSingleton::get_instance()->keybindings.find(keycode) != KeyBindingSingleton::get_instance()->keybindings.end()) {
			auto command = KeyBindingSingleton::get_instance()->keybindings.at(keycode);
			KeyBindingSingleton::get_instance()->keys_down.at(command) = true;
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