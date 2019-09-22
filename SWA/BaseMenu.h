#pragma once
class BaseMenu
{
public:
	virtual ~BaseMenu() = default;
	virtual void render() = 0;
	virtual void input() = 0;
	virtual void onMouseMove(int x, int y) = 0;
	virtual void onMouseButton(int button, bool pressed) = 0;
};
