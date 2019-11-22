#include "Credits.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"

Credits::~Credits() = default;

Credits::Credits(Engine::SceneManager* manager) : BaseScene(manager) { }

void Credits::render()
{
	const auto timer = Engine::pre_update();
	input();
	Engine::update_animation(background_.get(), 0, 0);
	Engine::render_texture(title_.get(), 250, 200, nullptr);
	Engine::render_texture(sub_title_.get(), 500, 300, nullptr);
	Engine::render_texture(mart_van_den_berg.get(), 500, 400, nullptr);
	Engine::render_texture(mark_donker.get(), 500, 450, nullptr);
	Engine::render_texture(renato_feroce.get(), 500, 500, nullptr);
	Engine::render_texture(sjors_ficken.get(), 500, 550, nullptr);
	Engine::render_texture(tom_roozen.get(), 500, 600, nullptr);
	Engine::render_texture(gijs_verdonschot.get(), 500, 650, nullptr);
	Engine::render_texture(helper.get(), 370, 800, nullptr);
	Engine::render(timer);
}

void Credits::input() {
	constexpr static int k_keydown = 0;
	constexpr static int k_stop = 2;

	auto inputs = Engine::GetInputs();

	//Quit if user wants to exit
	if (!std::get<k_stop>(inputs)) {
		is_running_ = false;
		return;
	}

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_RETURN)
		{
			scene_manager_->set_scene("mainmenu");
			break;
		}
	}
}

void Credits::cleanup() {}

bool Credits::init() {
	title_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle"));
	sub_title_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 40, { 255,0,0, 255 }, "Credits"));
	background_ = std::make_unique<Animation>(*Engine::load_animation("mainmenu.png", 3));
	background_->scale = 1280.0 / 960.0;
	mart_van_den_berg = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Mart van den Berg"));
	mark_donker = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Mark Donker"));
	renato_feroce = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Renato Feroce"));
	sjors_ficken = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Sjors Ficken"));
	tom_roozen = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Tom Roozen"));
	gijs_verdonschot = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Gijs Verdonschot"));
	helper = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 },
		"Press ENTER to quit to main menu"));
	return true;
}