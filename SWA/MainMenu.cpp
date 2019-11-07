#include "MainMenu.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"

MainMenu::~MainMenu() = default;

MainMenu::MainMenu(SceneManager* manager) : BaseScene(manager) { }

void MainMenu::render()
{
	const auto timer = Engine::PreUpdate();
	input();
	Engine::UpdateAnimation(background_.get(), 0, 0);
	Engine::RenderTexture(title_.get(), 250, 200, nullptr);
	Engine::RenderTexture(start_.get(), 500, 400, nullptr);
	Engine::RenderTexture(settings_.get(), 500, 500, nullptr);
	Engine::RenderTexture(quit_.get(), 500, 600, nullptr);
	Engine::RenderTexture(helper_.get(), 115, 800, nullptr);
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
				auto core = std::make_unique<Core>(scene_manager_);
				scene_manager_->add_scene(std::move(core));
				//Engine::StopMusic();
				scene_manager_->push_scene();
				//Engine::PlayMusic("ingame.wav");
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
	title_->free_texture();
	start_->free_texture();
	settings_->free_texture();
	quit_->free_texture();
	helper_->free_texture();
	selector_->free_texture();
}

bool MainMenu::init()
{
	if (!Engine::InitRenderer("Demonic Dungeon Castle", false, 1280, 960)) {
		return false;
	}
	//if (!Engine::InitAudio()) {
		//return false;
	//}
	title_ = Engine::LoadText("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle");
	background_ = Engine::LoadAnimation("mainmenu.png", 3);
	background_->scale = 1280.0 / 960.0;
	start_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Start game");
	settings_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Settings");
	quit_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Quit to desktop");
	selector_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, ">");
	helper_ = Engine::LoadText("manaspc.ttf", 24, {255, 255, 255, 255},
	                          "Use the arrow keys ^` to navigate the menu and ENTER to confirm");
	//Engine::PlayMusic("mainmenu.wav");
	return true;
}

