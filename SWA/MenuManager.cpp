#include "MenuManager.h"
#include <utility>
menu_manager::menu_manager() = default;
menu_manager::menu_manager(std::vector<std::shared_ptr<base_scene>> menus) : menus{std::move(menus)} {}

void menu_manager::add_menu(base_scene& menu)
{
	menus.emplace_back(std::shared_ptr<base_scene>(&menu));
}
void menu_manager::delete_menu(const std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<base_scene>>>> index)
{
	menus.erase(index);
}
void menu_manager::push_menu(base_scene& menu)
{
	activeMenus.push(std::shared_ptr<base_scene>(&menu));
}
void menu_manager::pop_menu()
{
	activeMenus.pop();
}

void menu_manager::draw()
{
	const auto currentMenu = &activeMenus.top();
	currentMenu->get()->render();
}

void menu_manager::input()
{
	const auto currentMenu = &activeMenus.top();
	currentMenu->get()->input();
}


