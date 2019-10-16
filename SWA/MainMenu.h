#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Animation.h"

class MainMenu :
	virtual public BaseScene
{
private:
	Texture* title_ = nullptr;
	Animation* background_ = nullptr;
	Texture* start_ = nullptr;
	Texture* settings_ = nullptr;
	Texture* quit_ = nullptr;
	uint8_t current_action_ = 0;
public:
	~MainMenu();
	MainMenu(SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};

