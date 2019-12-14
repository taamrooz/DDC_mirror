#include "SceneManager.h"

namespace Engine {
	SceneManager::SceneManager() = default;
	SceneManager::~SceneManager()
	{
		active_scenes_.clear();
	}

	void SceneManager::add_scene(BaseScene* scene, bool init, std::string name)
	{
		active_scenes_.insert(std::make_pair(name, std::unique_ptr<BaseScene>(scene)));
		if (init)
		{
			active_scenes_.at(name)->init();
		}
	}

	void SceneManager::delete_scene(std::string name)
	{
		if (active_scenes_.find(name) != active_scenes_.end()) {
			active_scenes_.at(name)->cleanup();
			active_scenes_.erase(name);
		}
	}

	void SceneManager::set_scene(std::string name)
	{
		if (active_scenes_.find(name) != active_scenes_.end()) {
			current_scene_ = name;
		}
	}

	void SceneManager::render()
	{
		if (!active_scenes_.empty()) {
			if (active_scenes_[current_scene_]) {
				while (active_scenes_[current_scene_]->get_is_running())
				{
					active_scenes_[current_scene_]->render();
				}
			}
		}
	}

	void SceneManager::cleanup()
	{
		for (auto& scene : active_scenes_)
		{
			scene.second->cleanup();
		}
	}

	bool SceneManager::init()
	{
		return active_scenes_[current_scene_]->init();
	}
}