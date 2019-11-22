#pragma once
#include <memory>
#include <vector>
#include "BaseScene.h"
#include <unordered_map>

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
		std::unordered_map<std::string, std::unique_ptr<BaseScene>> active_scenes_;
		std::string current_scene_;
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
		ENGINE_API void add_scene(BaseScene* scene, bool init, std::string);

		/**
		 * \brief Deletes the last scene in the active scenes collection.
		 */
		ENGINE_API void delete_scene(std::string name);

		ENGINE_API void set_scene(std::string name);

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
