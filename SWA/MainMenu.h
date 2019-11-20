#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Animation.h"

class MainMenu :
	virtual public Engine::BaseScene
{
private:
	std::unique_ptr<Texture> title_ = nullptr;
	std::unique_ptr<Animation> background_ = nullptr;
	std::unique_ptr<Texture> start_ = nullptr;
	std::unique_ptr<Texture> settings_ = nullptr;
	std::unique_ptr<Texture> credits_ = nullptr;
	std::unique_ptr<Texture> help_ = nullptr;
	std::unique_ptr<Texture> level_editor_ = nullptr;
	std::unique_ptr<Texture> quit_ = nullptr;
	std::unique_ptr<Texture> selector_ = nullptr;
	std::unique_ptr<Texture> helper = nullptr;
	uint8_t current_action_ = 0;
public:
	~MainMenu();
	MainMenu(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};

