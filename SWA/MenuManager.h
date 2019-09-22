#pragma once
#include <stack>
#include <memory>
#include "BaseMenu.h"
#include <vector>

class MenuManager
{
private:
	std::vector<std::unique_ptr<BaseMenu>> menus;
	std::stack<std::unique_ptr<BaseMenu>> activeMenus;
public:
	MenuManager();
	MenuManager(std::vector<std::unique_ptr<BaseMenu>>& menus);
	void addMenu(BaseMenu& menu);
	void deleteMenu(std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::unique_ptr<BaseMenu>>>> index);
	void pushMenu(BaseMenu& menu);
	void popMenu();
	void draw();
	void input();
};

