#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Animation.h"
#include "Timer.h"

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
	std::unique_ptr<Texture> start_ = nullptr;
	std::unique_ptr<Texture> settings_ = nullptr;
	std::unique_ptr<Texture> credits_ = nullptr;
	std::unique_ptr<Texture> help_ = nullptr;
	std::unique_ptr<Texture> level_editor_ = nullptr;
	std::unique_ptr<Texture> quit_ = nullptr;
	std::unique_ptr<Texture> selector_ = nullptr;
	std::unique_ptr<Texture> helper = nullptr;
	uint8_t current_action_ = 0;
	Engine::Timer timer_{};
public:
	~MainMenu();
	MainMenu(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};

