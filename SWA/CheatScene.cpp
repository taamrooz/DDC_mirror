#include "CheatScene.h"
#include "Renderer.h"
#include "Audio.h"
#include <chrono>
#include <thread>
#include "UserInput.h"
#include "SceneManager.h"
#include "KeyBindingSingleton.h"

CheatScene::CheatScene(Engine::SceneManager* manager) : BaseScene(manager) { }

void CheatScene::render()
{
	const auto timer = Engine::pre_update();
	input();
	Engine::update_animation(background_.get(), 0, 0);
	Engine::render_texture(title_.get(), 250, 125, nullptr);
	Engine::render_texture(sub_title_.get(), 525, 300, nullptr);
	Engine::render_texture(speedhack_.get(), 425, 425, nullptr);
	Engine::render_texture(regain_health_.get(), 425, 475, nullptr);
	Engine::render_texture(teleport_.get(), 425, 525, nullptr);
	Engine::render_texture(next_room_.get(), 425, 575, nullptr);
	Engine::render_texture(kill_all_.get(), 425, 625, nullptr);
	Engine::render_texture(speed_up_.get(), 425, 675, nullptr);
	Engine::render_texture(speed_down_.get(), 425, 725, nullptr);
	Engine::render_texture(return_.get(), 370, 850, nullptr);
	Engine::render(timer);
}

void CheatScene::cleanup()
{
}

bool CheatScene::init()
{
	title_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle"));
	sub_title_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 40, { 255,0,0, 255 }, "Cheats"));
	background_ = std::unique_ptr<Animation>(Engine::load_animation("mainmenu.png", 3));
	background_->scale = 1280.0 / 960.0;
	speedhack_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, (    "Hold down to move faster: " + KeyBindingSingleton::get_instance()->get_speedhack_key()).c_str()));
	regain_health_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, ("Regain all health:        " + KeyBindingSingleton::get_instance()->get_invincible_key()).c_str()));
	teleport_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, (     "Teleport:                 " + KeyBindingSingleton::get_instance()->get_teleport_key()).c_str()));
	next_room_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, (    "Go into the next room:    " + KeyBindingSingleton::get_instance()->get_next_room_key()).c_str()));
	kill_all_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, (     "Kill all enemies:         " + KeyBindingSingleton::get_instance()->get_kill_all_key()).c_str()));
	speed_up_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, (     "Increase game speed:      " + KeyBindingSingleton::get_instance()->get_gamespeed_increase()).c_str()));
	speed_down_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, ("   Decrease game speed:      " + KeyBindingSingleton::get_instance()->get_gamespeed_decrease()).c_str()));
	return_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 }, "Press ENTER to go back to the Help menu"));
	return true;
}

void CheatScene::input()
{
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
			scene_manager_->set_scene("help");
			Engine::play_music("help.wav");
			break;
		}
	}
}
