#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Animation.h"

class Help :
	virtual public BaseScene
{
private:
	Texture* title_ = nullptr;
	Texture* sub_title_moving_ = nullptr;
	Texture* sub_title_shooting_ = nullptr;
	Animation* background_ = nullptr;
	Texture* move_up_ = nullptr;
	Texture* move_left_ = nullptr;
	Texture* move_right_ = nullptr;
	Texture* move_down_ = nullptr;
	Texture* shoot_up_ = nullptr;
	Texture* shoot_left_ = nullptr;
	Texture* shoot_right_ = nullptr;
	Texture* shoot_down_ = nullptr;
	Texture* helper = nullptr;
public:
	~Help();
	Help(SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};