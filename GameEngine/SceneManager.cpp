#include "SceneManager.h"

namespace Engine {
	SceneManager::SceneManager() = default;
	SceneManager::~SceneManager()
	{
		active_scenes_.clear();
	}

	void SceneManager::add_scene(BaseScene* scene, bool init)
	{
		active_scenes_.push_back(std::unique_ptr<BaseScene>(scene));
		if (init)
		{
			active_scenes_.back()->init();
		}
	}

	void SceneManager::delete_scene()
	{
		active_scenes_.back()->cleanup();
		active_scenes_.pop_back();
	}

	SceneManager& SceneManager::push_scene()
	{
		if (current_scene_ < active_scenes_.size())
		{
			++current_scene_;
		}
		return *this;
	}

	SceneManager& SceneManager::pop_scene()
	{
		if (current_scene_ > 0)
		{
			--current_scene_;
		}
		return *this;
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
			scene->cleanup();
		}
	}

	bool SceneManager::init()
	{
		return active_scenes_[current_scene_]->init();
	}
}