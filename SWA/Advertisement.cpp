#include "Advertisement.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include <Audio.h>

Advertisement::~Advertisement() = default;

Advertisement::Advertisement(Engine::SceneManager* manager) : BaseScene(manager) { }

void Advertisement::render() {

}

void Advertisement::input() {
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
			Engine::stop_music();
			Engine::play_music("low.wav");
			std::this_thread::sleep_for(std::chrono::milliseconds(112));

			Engine::stop_music();
			scene_manager_->set_scene("mainmenu");
			Engine::play_music("mainmenu.wav");
			break;
		}
	}
}

void Advertisement::cleanup() {}

bool Advertisement::init() {
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