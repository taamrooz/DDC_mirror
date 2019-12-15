#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Animation.h"
#include "Core.h"

class Advertisement :
	virtual public Engine::BaseScene
{
private:
	std::unique_ptr<Animation> exit_ = nullptr;
	std::unique_ptr<Animation> advertisement_ = nullptr;
	constexpr static int k_lmb_ = 1;
public:
	~Advertisement();
	Advertisement(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};