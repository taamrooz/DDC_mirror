#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Animation.h"
#include <memory>

class Credits :
	virtual public Engine::BaseScene
{
private:
	std::unique_ptr<Texture> title_ = nullptr;
	std::unique_ptr<Texture> sub_title_ = nullptr;
	std::unique_ptr<Animation> background_ = nullptr;
	std::unique_ptr<Texture> mart_van_den_berg = nullptr;
	std::unique_ptr<Texture> mark_donker = nullptr;
	std::unique_ptr<Texture> renato_feroce = nullptr;
	std::unique_ptr<Texture> sjors_ficken = nullptr;
	std::unique_ptr<Texture> tom_roozen = nullptr;
	std::unique_ptr<Texture> gijs_verdonschot = nullptr;
	std::unique_ptr<Texture> helper = nullptr;
public:
	~Credits();
	Credits(Engine::SceneManager* manager);
	void render() override;
	void cleanup() override;
	bool init() override;
	void input();
};
