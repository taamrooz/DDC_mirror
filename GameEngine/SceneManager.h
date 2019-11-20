#pragma once
#include <memory>
#include <vector>
#include "BaseScene.h"

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine {
	class BaseScene;
	
	class SceneManager
	{
	private:
		std::vector<std::unique_ptr<BaseScene>> active_scenes_;
		unsigned int current_scene_{0};
	public:
		ENGINE_API SceneManager();
		ENGINE_API ~SceneManager();
		ENGINE_API SceneManager& operator=(const SceneManager& other) = delete;
		ENGINE_API SceneManager& operator=(SceneManager&& other) = delete;
		ENGINE_API SceneManager(const SceneManager& other) = delete;
		ENGINE_API SceneManager(SceneManager&& other) = delete;
		/**
		 * \brief Adds a scene to the collection of active scenes.
		 * @param scene Pointer to the scene being added, the SceneManager claims ownership of this pointer.
		 * @param init: Boolean to indicate whether or not the scene's init function should be called.
		 */
		ENGINE_API void add_scene(BaseScene* scene, bool init);

		/**
		 * \brief Deletes the last scene in the active scenes collection.
		 */
		ENGINE_API void delete_scene();

		/**
		 * \brief Increases the current scene by 1.
		 * @return Returns reference of SceneManager to allow for chaining (i.e. manager_->push_scene().push_scene(); )
		 */
		ENGINE_API SceneManager& push_scene();

		/**
		 * \brief Decreases the current scene by 1.
		 * @return Returns reference to SceneManager to allow for chaining (i.e. manager_->pop_scene().pop_scene(); )
		 */
		ENGINE_API SceneManager& pop_scene();

		/**
		 * \brief Based on the currently active scene, that scene will render.
		 */
		ENGINE_API void render();

		/**
		 * \brief Calls the cleanup function for all scenes.
		 */
		ENGINE_API void cleanup();

		/**
		 * \brief Initializes the currently active scene in the active scenes collection.
		 */
		ENGINE_API bool init();
	};
}
