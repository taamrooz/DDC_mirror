#pragma once
#include "EntityManager.h"
#include "BaseSystem.h"
#include "AnimationComponent.h"
#include "VelocityComponent.h"
#include "BaseScene.h"
#include "SceneManager.h"

class Core : virtual public BaseScene
{
private:
	std::vector<std::unique_ptr<BaseSystem>> systems_;
	std::unique_ptr<Engine::EntityManager<Component>> manager_ = nullptr;
	/*
	 * Loops through all systems and calls their respective update function.
	 */
	void update();
	
public:
	Core(SceneManager* manager);
	~Core();
	/*
	 * Initializes the core by creating the entity manager, systems and components.
	 */
	bool init() override;
	/*
	 * Renders to the screen by calling our update function and using the engine to render.
	 */
	void render() override;
	/*
	 * Cleans up the core by deleting the entity manager and all systems.
	 */
	void cleanup() override;
	/*
	 * Sets is_running to false, which will stop rendering.
	 */
	void StopGameLoop();
};

