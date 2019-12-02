#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include <memory>
#include "Animation.h"

class CheatScene : virtual public Engine::BaseScene
{
private:
	std::unique_ptr<Texture> title_ = nullptr;
	std::unique_ptr<Texture> sub_title_ = nullptr;
	std::unique_ptr<Animation> background_ = nullptr;
	std::unique_ptr<Texture> regain_health_ = nullptr;
	std::unique_ptr<Texture> move_left_ = nullptr;
	std::unique_ptr<Texture> move_right_ = nullptr;
	std::unique_ptr<Texture> move_down_ = nullptr;
	std::unique_ptr<Texture> return_ = nullptr;
public:
	CheatScene(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};

