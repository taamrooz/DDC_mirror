#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Animation.h"

class MainMenu :
	virtual public BaseScene
{
private:
	std::unique_ptr<Texture> title_;
	std::unique_ptr<Animation> background_;
	std::unique_ptr<Texture> start_;
	std::unique_ptr<Texture> settings_;
	std::unique_ptr<Texture> quit_;
	std::unique_ptr<Texture> selector_;
	std::unique_ptr<Texture> helper_;
	uint8_t current_action_ = 0;
public:
	~MainMenu();
	MainMenu(SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};

