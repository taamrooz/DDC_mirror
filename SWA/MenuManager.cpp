#include "MenuManager.h"
#include <utility>
MenuManager::MenuManager() = default;
MenuManager::MenuManager(std::vector<std::unique_ptr<BaseMenu>> menus) : menus{std::move(menus)} {}

void MenuManager::addMenu(BaseMenu& menu)
{
	//menus.emplace_back(std::make_unique<BaseMenu>(menu));
}
void MenuManager::deleteMenu(const std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::unique_ptr<BaseMenu>>>> index)
{
	menus.erase(index);
}
void MenuManager::pushMenu(BaseMenu& menu)
{
	//activeMenus.push(std::make_unique<BaseMenu>(menu));
}
void MenuManager::popMenu()
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


