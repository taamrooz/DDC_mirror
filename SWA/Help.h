#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Animation.h"
#include <memory>

class Help :
	virtual public Engine::BaseScene
{
private:
	std::unique_ptr<Texture> title_ = nullptr;
	std::unique_ptr<Texture> sub_title_moving_ = nullptr;
	std::unique_ptr<Texture> sub_title_shooting_ = nullptr;
	std::unique_ptr<Animation> background_ = nullptr;
	std::unique_ptr<Texture> move_up_ = nullptr;
	std::unique_ptr<Texture> move_left_ = nullptr;
	std::unique_ptr<Texture> move_right_ = nullptr;
	std::unique_ptr<Texture> move_down_ = nullptr;
	std::unique_ptr<Texture> shoot_up_ = nullptr;
	std::unique_ptr<Texture> shoot_left_ = nullptr;
	std::unique_ptr<Texture> shoot_right_ = nullptr;
	std::unique_ptr<Texture> shoot_down_ = nullptr;
	std::unique_ptr<Texture> helper = nullptr;
public:
	~Help();
	Help(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};
