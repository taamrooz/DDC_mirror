#pragma once

namespace Engine {
	class SceneManager;


	class BaseScene
	{
	public:
		SceneManager* scene_manager_;
		BaseScene(SceneManager* manager) : scene_manager_(manager) {}
		BaseScene& operator=(const BaseScene& other) = delete;
		BaseScene& operator=(BaseScene&& other) = delete;
		BaseScene(const BaseScene& other) = delete;
		BaseScene(BaseScene&& other) = delete;
		virtual ~BaseScene() {};
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
		bool get_is_running() const { return is_running_; }
	protected:
		bool is_running_ = true;
	};
}
