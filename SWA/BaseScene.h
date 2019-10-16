#pragma once
class SceneManager;
#include "SceneManager.h"

class BaseScene
{
public:
	SceneManager* scene_manager_;
	BaseScene(SceneManager* manager) : scene_manager_(manager) {}
	virtual ~BaseScene() = default;
	virtual bool init() = 0;
	virtual void render() = 0;
	virtual void cleanup() = 0;
	bool is_running = true;
	
};
