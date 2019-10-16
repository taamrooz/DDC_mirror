#pragma once
#include <stack>
#include <memory>
#include <vector>
class BaseScene;
#include "BaseScene.h"

class SceneManager
{
private:
	//std::vector<std::unique_ptr<BaseScene>> scenes_;
	std::vector<std::unique_ptr<BaseScene>> active_scenes_;
	uint16_t current_scene_ = 0;
public:
	SceneManager();
	~SceneManager();
	void add_scene(BaseScene& menu);
	void delete_scene();
	void push_scene();
	void pop_scene();
	void render();
	void cleanup();
	bool init();
};

