#pragma once
class base_scene
{
public:
	virtual ~base_scene() = 0;
	virtual void render() = 0;
	virtual void input() = 0;
	virtual void on_mouse_move(int x, int y) = 0;
	virtual void on_mouse_button(int button, bool pressed) = 0;
};
