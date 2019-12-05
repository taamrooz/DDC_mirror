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
	std::unique_ptr<Texture> teleport_ = nullptr;
	std::unique_ptr<Texture> next_room_ = nullptr;
	std::unique_ptr<Texture> kill_all_ = nullptr;
	std::unique_ptr<Texture> return_ = nullptr;
public:
	CheatScene(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};

