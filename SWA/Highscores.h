#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Animation.h"
#include <memory>

class Highscores :
	virtual public Engine::BaseScene
{
private:
	std::unique_ptr<Texture> title_ = nullptr;
	std::unique_ptr<Animation> background_ = nullptr;
	std::unique_ptr<Texture> helper_ = nullptr;
	std::unique_ptr<Texture> highscore_ = nullptr;
	std::unique_ptr<Texture> explanation_ = nullptr;
	std::vector<std::unique_ptr<Texture>> highscore_textures_;
	void get_highscores();
  
public:
	Highscores(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};
