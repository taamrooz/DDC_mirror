#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Animation.h"

class EndGame :
	virtual public BaseScene
{
private:
	Texture* title_ = nullptr;
	Texture* sub_title_ = nullptr;
	Animation* background_ = nullptr;
	Texture* helper = nullptr;
	uint8_t current_action_ = 0;
public:
	~EndGame();
	EndGame(SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};