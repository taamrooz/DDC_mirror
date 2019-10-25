#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Animation.h"

class Pause :
	virtual public BaseScene
{
private:
	Texture* title_ = nullptr;
	Animation* background_ = nullptr;
	uint8_t current_action_ = 0;
public:
	~Pause();
	Pause(SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};