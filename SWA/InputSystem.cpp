#include "InputSystem.h"
#include "UserInput.h"


InputSystem::InputSystem(EntityManager* manager, InputComponent* inputcomponent, Core &core) : BaseSystem(manager) {
	InputSystem::core = &core;
	input_component = inputcomponent;
}

void InputSystem::update(double dt)
{
	auto user_inputs = Engine::GetInputs();
	if (!user_inputs.second) {
		core->StopGameLoop();
		return;
	}
	for (const auto& keycode : user_inputs.first)
	{
		if(keycode == SDLK_q)
		{
			core->scene_manager_->pop_scene();
			break;
		}
		if (input_component->keybindings.find(keycode) != input_component->keybindings.end()) {
			auto command = input_component->keybindings.at(keycode);
			input_component->keys_down.at(command) = true;
		}
	}
}