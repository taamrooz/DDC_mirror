#include "Advertisement.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include <Audio.h>
#include <iostream>
#include <thread>

Advertisement::~Advertisement() = default;

Advertisement::Advertisement(Engine::SceneManager* manager) : BaseScene(manager) { }

void Advertisement::render() {
	const auto timer = Engine::pre_update();
	input();

	Engine::update_animation(advertisement_.get(), 300, 30);
	Engine::update_animation(exit_.get(), 1200, 30);
	Engine::render(timer);
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
			auto mouse_pos = Engine::GetMouseState();
			if (mouse_pos.first >= 1205 && mouse_pos.first <= 1225 &&
				mouse_pos.second >= 30 && mouse_pos.second <= 55) 
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
	advertisement_ = std::make_unique<Animation>(*Engine::load_animation("mediamarkt.png", 1, true));
	advertisement_->scale = 0.75;
	exit_ = std::make_unique<Animation>(*Engine::load_animation("Sprites/delete.png", 1, false));
	exit_->scale = 1.25;
	return true;
}