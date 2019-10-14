#include "InputSystem.h"
#include "UserInput.h"
#include "KeyBindingSingleton.h"


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
		if (KeyBindingSingleton::get_instance()->keybindings.find(keycode) != KeyBindingSingleton::get_instance()->keybindings.end()) {
			auto command = KeyBindingSingleton::get_instance()->keybindings.at(keycode);
			KeyBindingSingleton::get_instance()->keys_down.at(command) = true;
		}
	}
}