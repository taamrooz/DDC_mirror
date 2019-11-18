#include "MainMenu.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"
#include "Credits.h"

MainMenu::~MainMenu() = default;

MainMenu::MainMenu(SceneManager* manager) : BaseScene(manager) { }

void MainMenu::render()
{
	const auto timer = Engine::PreUpdate();
	input();

	Engine::UpdateAnimation(background_, 0, 0);
	Engine::RenderTexture(title_, 250, 200, nullptr);
	Engine::RenderTexture(start_, 500, 350, nullptr);
	Engine::RenderTexture(settings_, 500, 450, nullptr);
	Engine::RenderTexture(level_editor_, 500, 550, nullptr);
	Engine::RenderTexture(credits_, 500, 650, nullptr);
	Engine::RenderTexture(help_, 500, 750, nullptr);
	Engine::RenderTexture(quit_, 500, 850, nullptr);
	Engine::RenderTexture(helper, 115, 900, nullptr);
	if (current_action_ == 0)
	{
		Engine::RenderTexture(selector_, 480, 350, nullptr);
	}
	else if (current_action_ == 1)
	{
		Engine::RenderTexture(selector_, 480, 450, nullptr);
	}
	else if (current_action_ == 2)
	{
		Engine::RenderTexture(selector_, 480, 550, nullptr);
	}
	else if (current_action_ == 3)
	{
		Engine::RenderTexture(selector_, 480, 650, nullptr);
	}
	else if (current_action_ == 4)
	{
		Engine::RenderTexture(selector_, 480, 750, nullptr);
	}
	else if (current_action_ == 5)
	{
		Engine::RenderTexture(selector_, 480, 850, nullptr);
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
			if (current_action_ < 5)
			{
				++current_action_;
			}
		}
		else if (keycode == SDLK_RETURN)
		{
			switch (current_action_) {
			case 0:
				Engine::StopMusic();
				scene_manager_->push_scene();
				Engine::PlayMusic("ingame.wav");
				break;
			case 1:
				break;
			case 2:
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				break;
			case 3:
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				break;
			case 4:
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				break;
			case 5:
				is_running = false;
				scene_manager_->pop_scene();
				break;
			}
			
			if (!is_running) {
				break;
			}
		}
	}
}


void MainMenu::cleanup()
{
	delete background_;
	delete title_;
	delete start_;
	delete settings_;
	delete credits_;
	delete quit_;
	delete helper;
	delete selector_;
	Engine::DestroyRenderer();
	Engine::CloseAudio();
}

bool MainMenu::init()
{
	if (!Engine::InitRenderer("Demonic Dungeon Castle", false, 1280, 960)) {
		return false;
	}
	if (!Engine::InitAudio()) {
		return false;
	}
	title_ = Engine::LoadText("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle");
	background_ = &Engine::LoadAnimation("mainmenu.png", 3);
	background_->scale = 1280.0 / 960.0;
	start_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Start game");
	settings_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Settings");
	credits_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Credits");
	help_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Help");
	level_editor_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Level Editor");
	quit_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Quit to desktop");
	selector_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, ">");
	helper = Engine::LoadText("manaspc.ttf", 24, {255, 255, 255, 255},
	                          "Use the arrow keys ^` to navigate the menu and press ENTER to confirm");
	Engine::PlayMusic("mainmenu.wav");
	return true;
}

