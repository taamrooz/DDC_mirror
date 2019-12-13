#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Animation.h"
#include "Core.h"
#include <memory>

class Core;

class Pause :
	virtual public Engine::BaseScene
{
private:
	Core* core_;
	std::unique_ptr<Texture> title_ = nullptr;
	std::unique_ptr<Texture> paused_texture_ = nullptr;
	std::unique_ptr<Texture> helper_ = nullptr;
	std::unique_ptr<Animation> background_ = nullptr;
	std::string save_text_;
public:
	~Pause();
	Pause(Engine::SceneManager* manager, Core* core);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};
