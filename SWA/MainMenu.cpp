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
	Engine::Clear();
	input();

	Engine::UpdateAnimation(background_.get(), 0, 0);
	Engine::RenderTexture(title_.get(), 250, 200, nullptr);
	Engine::RenderTexture(start_.get(), 500, 400, nullptr);
	Engine::RenderTexture(settings_.get(), 500, 500, nullptr);
	Engine::RenderTexture(credits_.get(), 500, 600, nullptr);
	Engine::RenderTexture(help_.get(), 500, 700, nullptr);
	Engine::RenderTexture(quit_.get(), 500, 800, nullptr);
	Engine::RenderTexture(helper.get(), 115, 900, nullptr);
	if (current_action_ == 0)
	{
		Engine::RenderTexture(selector_.get(), 480, 400, nullptr);
	}
	else if (current_action_ == 1)
	{
		Engine::RenderTexture(selector_.get(), 480, 500, nullptr);
	}
	else if (current_action_ == 2)
	{
		Engine::RenderTexture(selector_.get(), 480, 600, nullptr);
	}
	else if (current_action_ == 3)
	{
		Engine::RenderTexture(selector_.get(), 480, 700, nullptr);
	}
	else if (current_action_ == 4)
	{
		Engine::RenderTexture(selector_.get(), 480, 800, nullptr);
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
			if (current_action_ < 4)
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
				scene_manager_->render();
				break;
			case 3:
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				scene_manager_->render();
				break;
			case 4:
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
	title_ = std::make_unique<Texture>(*Engine::LoadText("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle"));
	background_ = std::make_unique<Animation>(*Engine::LoadAnimation("mainmenu.png", 3));
	background_->scale = 1280.0 / 960.0;
	start_ = std::make_unique<Texture>(*Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Start game"));
	settings_ = std::make_unique<Texture>(*Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Settings"));
	credits_ = std::make_unique<Texture>(*Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Credits"));
	help_ = std::make_unique<Texture>(*Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Help"));
	quit_ = std::make_unique<Texture>(*Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Quit to desktop"));
	selector_ = std::make_unique<Texture>(*Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, ">"));
	helper = std::make_unique<Texture>(*Engine::LoadText("manaspc.ttf", 24, {255, 255, 255, 255},
	                          "Use the arrow keys ^` to navigate the menu and press ENTER to confirm"));
	Engine::PlayMusic("mainmenu.wav");
	return true;
}

