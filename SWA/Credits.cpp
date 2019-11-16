#include "Credits.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"

Credits::~Credits() = default;

Credits::Credits(SceneManager* manager) : BaseScene(manager) { }

void Credits::render()
{
	const auto timer = Engine::pre_update();
	input();
	Engine::update_animation(background_, 0, 0);
	Engine::render_texture(title_, 250, 200, nullptr);
	Engine::render_texture(sub_title_, 500, 300, nullptr);
	Engine::render_texture(mart_van_den_berg, 500, 400, nullptr);
	Engine::render_texture(mark_donker, 500, 450, nullptr);
	Engine::render_texture(renato_feroce, 500, 500, nullptr);
	Engine::render_texture(sjors_ficken, 500, 550, nullptr);
	Engine::render_texture(tom_roozen, 500, 600, nullptr);
	Engine::render_texture(gijs_verdonschot, 500, 650, nullptr);
	Engine::render_texture(helper, 370, 800, nullptr);
	Engine::render(timer);
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
			is_running = false;
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
	title_ = Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle");
	sub_title_ = Engine::load_text("manaspc.ttf", 40, { 255,0,0, 255 }, "Credits");
	background_ = Engine::load_animation("mainmenu.png", 3);
	background_->scale = 1280.0 / 960.0;
	mart_van_den_berg = Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Mart van den Berg");
	mark_donker = Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Mark Donker");
	renato_feroce = Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Renato Feroce");
	sjors_ficken = Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Sjors Ficken");
	tom_roozen = Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Tom Roozen");
	gijs_verdonschot = Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Gijs Verdonschot");
	helper = Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 },
		"Press ENTER to quit to main menu");
	return true;
}