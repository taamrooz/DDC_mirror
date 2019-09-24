#pragma once
#include <stack>
#include <memory>
#include "BaseScene.h"
#include <vector>

class menu_manager
{
private:
	std::vector<std::shared_ptr<base_scene>> menus;
	std::stack<std::shared_ptr<base_scene>> activeMenus;
public:
	menu_manager();
	menu_manager(std::vector<std::shared_ptr<base_scene>> menus);
	void add_menu(base_scene& menu);
	void delete_menu(std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<base_scene>>>> index);
	void push_menu(base_scene& menu);
	void pop_menu();
	void draw();
	void input();
};

