#pragma once
#include "BaseMenu.h"
#include "MenuManager.h"
class MainMenu :
	public BaseMenu
{
public:
	MainMenu();
	void render() override;
	void input() override;
	void onMouseMove(int x, int y) override;
	void onMouseButton(int button, bool pressed) override;
};

