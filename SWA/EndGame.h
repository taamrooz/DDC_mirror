#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Animation.h"
#include <memory>

class EndGame :
	virtual public Engine::BaseScene
{
private:
	std::unique_ptr<Texture> title_ = nullptr;
	std::unique_ptr<Texture> sub_title_ = nullptr;
	std::unique_ptr<Animation> background_ = nullptr;
	std::unique_ptr<Texture> helper_ = nullptr;
public:
	~EndGame();
	EndGame(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};
