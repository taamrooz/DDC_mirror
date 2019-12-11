#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Animation.h"
#include "Core.h"

class Advertisement :
	virtual public Engine::BaseScene
{
private:
	std::unique_ptr<Texture> exit_ = nullptr;
	std::unique_ptr<Animation> advertisement_ = nullptr;
public:
	~Advertisement();
	Advertisement(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};