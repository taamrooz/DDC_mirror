#pragma once
#include "EntityManager.h"
#include "BaseSystem.h"
#include "BaseScene.h"
#include "SceneManager.h"
#include "Timer.h"

class Core : virtual public Engine::BaseScene
{
private:
	std::vector<std::unique_ptr<BaseSystem>> systems_;
	std::unique_ptr<Engine::EntityManager<Component>> manager_ = nullptr;
	bool is_paused_ = false;
	bool is_winner_ = false;
	bool is_loser_ = false;
	bool new_game_{};
	double last_tick_{ 0 };
	double game_speed{ 1 };
	double elapsed_secs_ = 0;
	Engine::Timer timer_{};
	/*
	 * Loops through all systems and calls their respective update function.
	 */
	void update(double dt);
	
public:
	Core(Engine::SceneManager* manager, bool new_game);
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
	 * \brief Increases the gamespeed by 0.1
	 */
	void gamespeed_increase();
	/**
	 * \brief Decreases the gamespeed by 0.1
	 */
	void gamespeed_decrease();
	/**
	 * \brief Saves the game
	 * @params path path to save to
	 */
	void save_game(std::string path);
	/**
	 * \brief Returns entity manager pointer
	 */
	Engine::EntityManager<Component>* get_entity_manager();
	/**
	* \Unpauzes the timer which counts your highscore
	*/
	void unpauzeTimer();
};

