#include "SceneManager.h"

SceneManager::SceneManager() = default;
SceneManager::~SceneManager() = default;


void SceneManager::add_menu(BaseScene & menu)
{
	menus.emplace_back(std::unique_ptr<BaseScene>(&menu));
}
void SceneManager::delete_menu(const std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::unique_ptr<BaseScene>>>> index)
{
	menus.erase(index);
}
void SceneManager::push_menu(BaseScene & menu)
{
	activeMenus.push(std::unique_ptr<BaseScene>(&menu));
}
void SceneManager::pop_menu()
{
	activeMenus.pop();
}

void SceneManager::render()
{
	if (!activeMenus.empty()) {
		auto current_menu = &*activeMenus.top();
		while (current_menu->is_running)
		{
			current_menu = &*activeMenus.top();
			if(current_menu != nullptr)
			{
				current_menu->render();
			}
			
		}
	}

}

void SceneManager::cleanup()
{
	for (auto& scene : menus)
	{
		scene->cleanup();
	}
}

bool SceneManager::init()
{
	const auto current_menu = &*activeMenus.top();
	return current_menu->init();
}




