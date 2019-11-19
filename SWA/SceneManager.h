#pragma once
#include <memory>
#include <vector>
class BaseScene;
#include "BaseScene.h"

class SceneManager
{
private:
	std::vector<std::unique_ptr<BaseScene>> active_scenes_;
	uint8_t current_scene_ = 0;
public:
	SceneManager();
	~SceneManager();
	/*
	 * Adds a scene to the collection of active scenes.
	 */
	void add_scene(BaseScene& menu);

	/*
	 * Deletes the last scene in the active scenes collection.
	 */
	void delete_scene();

	/*
	 * Increases the current scene by 1.
	 */
	void push_scene();

	/*
	 * Decreases the current scene by 1.
	 */
	void pop_scene();

	/*
	 * Based on the currently active scene, the scene will render.
	 */
	void render();

	/*
	 * Calls the cleanup function for all scenes.
	 */
	void cleanup();

	/*
	 * Initializes the last scene in the active scenes collection.
	 */
	bool init();
};

