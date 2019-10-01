#include "MenuManager.h"
#include <utility>

MenuManager::MenuManager() = default;
MenuManager::MenuManager(std::vector<std::shared_ptr<BaseScene>> menus) : menus{std::move(menus)} {}

void MenuManager::add_menu(BaseScene& menu)
{
	menus.emplace_back(std::shared_ptr<BaseScene>(&menu));
}
void MenuManager::delete_menu(const std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<BaseScene>>>> index)
{
	menus.erase(index);
}
void MenuManager::push_menu(BaseScene& menu)
{
	activeMenus.push(std::shared_ptr<BaseScene>(&menu));
}
void MenuManager::pop_menu()
{
	activeMenus.pop();
}

void MenuManager::draw()
{
	const auto currentMenu = &activeMenus.top();
	currentMenu->get()->render();
}

void MenuManager::input()
{
	const auto currentMenu = &activeMenus.top();
	currentMenu->get()->input();
}


