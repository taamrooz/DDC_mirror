#pragma once
#include "EntityManager.h"
#include "BaseSystem.h"
#include "AnimationComponent.h"
#include "BaseScene.h"
#include "SceneManager.h"
#include "Timer.h"
#include "Pause.h"

class Core : virtual public Engine::BaseScene
{
private:
	std::vector<std::unique_ptr<BaseSystem>> systems_;
	std::unique_ptr<Engine::EntityManager<Component>> manager_ = nullptr;
	bool is_paused_ = false;
	bool is_winner_ = false;
	bool is_loser_ = false;
	double elapsed_secs_ = 0;
	Engine::Timer timer_{};
	/*
	 * Loops through all systems and calls their respective update function.
	 */
	void update();
	
public:
	Core(Engine::SceneManager* manager);
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
	/**
	 * \brief Returns true if the game is in a pause state.
	 * @return value of is_paused_
	 */
	bool get_is_paused() const;
	/**
	 * \brief Toggles the games pause state.
	 */
	void toggle_pause();
	/**
	 * \brief Toggles the games win state.
	 */
	void toggle_game_won();
	/**
	 * \brief Toggles the games lose state.
	 */
	void toggle_game_lost();
	/**
	* \Unpauzes the timer which counts your highscore
	*/
	void unpauzeTimer();
	/**
	 * \brief Saves the game
	 */
	void save_game();
};

