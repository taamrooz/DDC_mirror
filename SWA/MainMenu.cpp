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
	Engine::RenderTexture(title_, 250, 200, nullptr);
	Engine::RenderTexture(start_, 500, 400, nullptr);
	Engine::RenderTexture(settings_, 500, 500, nullptr);
	Engine::RenderTexture(quit_, 500, 600, nullptr);
	Engine::RenderTexture(helper, 115, 800, nullptr);
	if (current_action_ == 0)
	{
		Engine::RenderTexture(selector_, 480, 400, nullptr);
	}
	else if (current_action_ == 1)
	{
		Engine::RenderTexture(selector_, 480, 500, nullptr);
	}
	else if (current_action_ == 2)
	{
		Engine::RenderTexture(selector_, 480, 600, nullptr);
	}
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
		is_running = false;
		return;
	}

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_UP)
		{
			if (current_action_ > 0)
			{
				--current_action_;
			}

		}
		else if (keycode == SDLK_DOWN)
		{
			if (current_action_ < 2)
			{
				++current_action_;
			}
		}
		else if (keycode == SDLK_RETURN)
		{
			if (current_action_ == 0)
			{
				scene_manager_->push_scene();
			}
			else if (current_action_ == 2)
			{
				is_running = false;
				scene_manager_->pop_scene();
				break;
			}
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
	background_->scale = 1280.0 / 960.0;
	start_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Start game");
	settings_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Settings");
	quit_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Quit to desktop");
	selector_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, ">");
	helper = Engine::LoadText("manaspc.ttf", 24, {255, 255, 255, 255},
	                          "Use the arrow keys ^` to navigate the menu and ENTER to confirm");
	return true;
}

