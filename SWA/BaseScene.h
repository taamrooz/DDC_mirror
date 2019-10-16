#pragma once
class SceneManager;
#include "SceneManager.h"

class BaseScene
{
public:
	SceneManager* scene_manager_;
	BaseScene(SceneManager* manager) : scene_manager_(manager) {}
	virtual ~BaseScene() = default;
	/*
	 * Initializes the scene.
	 */
	virtual bool init() = 0;
	/*
	 * Renders to the screen.
	 */
	virtual void render() = 0;
	/*
	 * Destroys the scene.
	 */
	virtual void cleanup() = 0;
	bool is_running = true;
	
};
