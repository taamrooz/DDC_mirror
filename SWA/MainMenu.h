#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Animation.h"
#include "Timer.h"
#include "Core.h"
#include "LevelEditor.h"
#include "Credits.h"
#include "Help.h"
#include "Highscores.h"

class MainMenu :
	virtual public Engine::BaseScene
{
private:
	std::unique_ptr<Texture> title_ = nullptr;
	std::unique_ptr<Animation> background_ = nullptr;
	int current_advertisement_index;
	std::vector<std::unique_ptr<Animation>> banner;
	std::unique_ptr<Animation> nike_advertisement_ = nullptr;
	std::unique_ptr<Animation> phone_advertisement_ = nullptr;
	std::unique_ptr<Animation> oral_b_advertisement_ = nullptr;
	std::unique_ptr<Animation> football_advertisement_ = nullptr;
	std::unique_ptr<Texture> start_ = nullptr;
	std::unique_ptr<Texture> load_game_ = nullptr;
	std::unique_ptr<Texture> credits_ = nullptr;
	std::unique_ptr<Texture> help_ = nullptr;
	std::unique_ptr<Texture> level_editor_ = nullptr;
	std::unique_ptr<Texture> quit_ = nullptr;
	std::unique_ptr<Texture> selector_ = nullptr;
	std::unique_ptr<Texture> helper = nullptr;
	std::unique_ptr<Texture> highscore_ = nullptr;
	uint8_t current_action_ = 0;
	Engine::Timer timer_{};
	void start_new_game();
	void start_level_editor();
public:
	~MainMenu();
	MainMenu(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};

