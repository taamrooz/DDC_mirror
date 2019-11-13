#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Animation.h"

class Credits :
	virtual public BaseScene
{
private:
	Texture* title_ = nullptr;
	Texture* sub_title_ = nullptr;
	Animation* background_ = nullptr;
	Texture* mart_van_den_berg = nullptr;
	Texture* mark_donker = nullptr;
	Texture* renato_feroce = nullptr;
	Texture* sjors_ficken = nullptr;
	Texture* tom_roozen = nullptr;
	Texture* gijs_verdonschot = nullptr;
	Texture* helper = nullptr;
public:
	~Credits();
	Credits(SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};
