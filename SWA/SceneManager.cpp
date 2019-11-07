#include "SceneManager.h"

SceneManager::SceneManager() = default;
SceneManager::~SceneManager()
{
	active_scenes_.clear();
}

void SceneManager::add_scene(std::unique_ptr<BaseScene> menu)
{
	active_scenes_.push_back(std::move(menu));
}

void SceneManager::delete_scene()
{
	delete_last = true;
	pop_scene();
}

void SceneManager::push_scene()
{
	if(active_scenes_.size() - 1 > current_scene_)
	{
		++current_scene_;
	}
	active_scenes_[current_scene_]->init();
	
}

void SceneManager::pop_scene()
{
	if(current_scene_ > 0)
	{
		--current_scene_;
	}
}

void SceneManager::render()
{
	
	if (!active_scenes_.empty()) {
		auto current_menu = &*active_scenes_[current_scene_];
		while (current_menu->is_running || delete_last)
		{
			if (delete_last)
			{
				active_scenes_.back()->cleanup();
				active_scenes_.pop_back();
				delete_last = false;
			}
			current_menu = &*active_scenes_[current_scene_];
			if(current_menu != nullptr)
			{
				current_menu->render();
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
	const auto current_menu = &*active_scenes_.back();
	return current_menu->init();
}