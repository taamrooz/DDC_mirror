#include "MainMenu.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"

MainMenu::~MainMenu() = default;

MainMenu::MainMenu(SceneManager * manager) : BaseScene(manager) { }

void MainMenu::render()
{
	const auto timer = Engine::PreUpdate();
	input();
	Engine::UpdateAnimation(background_, 0, 0);
	title_->render(250, 200, nullptr);
	start_->render(400, 300, nullptr);
	settings_->render(400, 400, nullptr);
	quit_->render(400, 500, nullptr);
	Engine::Render(timer);

}

void MainMenu::input()
{
	const int k_keydown = 0;
	const int k_keyup = 1;
	const int k_stop = 2;

	auto inputs = Engine::GetInputs();

	//Quit if user wants to exit
	if (!std::get<k_stop>(inputs)) {
		//core->StopGameLoop();
		return;
	}

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_q)
		{
			scene_manager_->pop_scene();
			break;
		}if (keycode == SDLK_g)
		{
			scene_manager_->push_scene();
		}
		if (KeyBindingSingleton::get_instance()->keybindings.find(keycode) != KeyBindingSingleton::get_instance()->keybindings.end()) {
			auto command = KeyBindingSingleton::get_instance()->keybindings.at(keycode);
			KeyBindingSingleton::get_instance()->keys_down.at(command) = true;
		}
	}

	//Handle all key up events
	for (const auto& keycode : std::get<k_keyup>(inputs))
	{
		if (KeyBindingSingleton::get_instance()->keybindings.find(keycode) != KeyBindingSingleton::get_instance()->keybindings.end()) {
			auto command = KeyBindingSingleton::get_instance()->keybindings.at(keycode);
			KeyBindingSingleton::get_instance()->keys_down.at(command) = false;
		}
	}
}


void MainMenu::cleanup()
{
	Engine::DestroyRenderer();
	Engine::CloseAudio();
}

bool MainMenu::init()
{
	if (!Engine::InitRenderer("Demonic Dungeon Crawler", false, 1280, 960)) {
		return false;
	}
	if (!Engine::InitAudio()) {
		return false;
	}
	title_ = Engine::LoadText("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Crawler");
	background_ = &Engine::LoadAnimation("mainmenu.png", 3);
	start_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Start game");
	settings_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Settings");
	quit_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Quit to desktop");
	return true;
}

