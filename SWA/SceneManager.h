#pragma once
#include <stack>
#include <memory>
#include <vector>
class BaseScene;
#include "BaseScene.h"

class SceneManager
{
private:
	std::vector<std::unique_ptr<BaseScene>> menus;
	std::stack<std::unique_ptr<BaseScene>> activeMenus;
public:
	SceneManager();
	~SceneManager();
	void add_menu(BaseScene& menu);
	void delete_menu(std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::unique_ptr<BaseScene>>>> index);
	void push_menu(BaseScene& menu);
	void pop_menu();
	void render();
	void cleanup();
	bool init();
};

