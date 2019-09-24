#pragma once
#include <stack>
#include <memory>
#include "BaseScene.h"
#include <vector>

class MenuManager
{
private:
	std::vector<std::shared_ptr<BaseScene>> menus;
	std::stack<std::shared_ptr<BaseScene>> activeMenus;
public:
	MenuManager();
	MenuManager(std::vector<std::shared_ptr<BaseScene>> menus);
	void add_menu(BaseScene& menu);
	void delete_menu(std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<BaseScene>>>> index);
	void push_menu(BaseScene& menu);
	void pop_menu();
	void draw();
	void input();
};

