#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"

class MainMenu :
	virtual public BaseScene
{
private:
	Texture* title{};
public:
	~MainMenu();
	MainMenu(SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
};

