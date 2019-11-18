#include "Credits.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"

Credits::~Credits() = default;

Credits::Credits(SceneManager* manager) : BaseScene(manager) { }

void Credits::render()
{
	const auto timer = Engine::PreUpdate();
	input();
	Engine::UpdateAnimation(background_, 0, 0);
	Engine::RenderTexture(title_, 250, 200, nullptr);
	Engine::RenderTexture(sub_title_, 500, 300, nullptr);
	Engine::RenderTexture(mart_van_den_berg, 500, 400, nullptr);
	Engine::RenderTexture(mark_donker, 500, 450, nullptr);
	Engine::RenderTexture(renato_feroce, 500, 500, nullptr);
	Engine::RenderTexture(sjors_ficken, 500, 550, nullptr);
	Engine::RenderTexture(tom_roozen, 500, 600, nullptr);
	Engine::RenderTexture(gijs_verdonschot, 500, 650, nullptr);
	Engine::RenderTexture(helper, 370, 800, nullptr);
	Engine::Render(timer);
}

void Credits::input() {
	const int k_keydown = 0;
	const int k_stop = 2;

	auto inputs = Engine::GetInputs();

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_RETURN)
		{
			scene_manager_->pop_scene();
			scene_manager_->pop_scene();
			scene_manager_->pop_scene();
			break;
		}
	}
}

void Credits::cleanup() {
	delete background_;
	delete title_;
	delete mart_van_den_berg;
	delete mark_donker;
	delete renato_feroce;
	delete sjors_ficken;
	delete tom_roozen;
	delete gijs_verdonschot;
	delete helper;
}

bool Credits::init() {
	title_ = Engine::LoadText("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle");
	sub_title_ = Engine::LoadText("manaspc.ttf", 40, { 255,0,0, 255 }, "Credits");
	background_ = &Engine::LoadAnimation("mainmenu.png", 3);
	background_->scale = 1280.0 / 960.0;
	mart_van_den_berg = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Mart van den Berg");
	mark_donker = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Mark Donker");
	renato_feroce = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Renato Feroce");
	sjors_ficken = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Sjors Ficken");
	tom_roozen = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Tom Roozen");
	gijs_verdonschot = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Gijs Verdonschot");
	helper = Engine::LoadText("manaspc.ttf", 24, { 255, 255, 255, 255 },
		"Press ENTER to quit to main menu");
	return true;
}