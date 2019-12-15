#include "MainMenu.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include <mutex>
#include <chrono>
#include "Help.h"
#include "Credits.h"
#include "LevelEditor.h"
#include "LoadGame.h"
#include "Constants.h"
#include "Highscores.h"

MainMenu::~MainMenu() = default;

MainMenu::MainMenu(Engine::SceneManager* manager) : BaseScene(manager) { }

void MainMenu::render()
{
	scene_manager_->delete_scene("game");
	const auto timer = Engine::pre_update();
	input();

	Engine::update_animation(background_.get(), 0, 0);
	Engine::render_texture(title_.get(), 250, 200, nullptr);
	Engine::render_texture(start_.get(), 550, 320, nullptr);
	Engine::render_texture(load_game_.get(), 550, 400, nullptr);
	Engine::render_texture(level_editor_.get(), 550, 480, nullptr);
	Engine::render_texture(credits_.get(), 550, 560, nullptr);
	Engine::render_texture(help_.get(), 550, 640, nullptr);
	Engine::render_texture(highscore_.get(), 550, 720, nullptr);
	Engine::render_texture(quit_.get(), 550, 800, nullptr);
	Engine::render_texture(helper.get(), 115, 900, nullptr);
	
	if (current_action_ == 0)
	{
		Engine::render_texture(selector_.get(), 530, 320, nullptr);
	}
	else if (current_action_ == 1)
	{
		Engine::render_texture(selector_.get(), 530, 400, nullptr);
	}
	else if (current_action_ == 2)
	{
		Engine::render_texture(selector_.get(), 530, 480, nullptr);
	}
	else if (current_action_ == 3)
	{
		Engine::render_texture(selector_.get(), 530, 560, nullptr);
	}
	else if (current_action_ == 4)
	{
		Engine::render_texture(selector_.get(), 530, 640, nullptr);
	}
	else if (current_action_ == 5)
	{
		Engine::render_texture(selector_.get(), 530, 720, nullptr);
	}
	else if (current_action_ == 6) 
	{
		Engine::render_texture(selector_.get(), 530, 800, nullptr);
	}
	
	Engine::render(timer);

}

void MainMenu::input()
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
		if (keycode == SDLK_UP)
		{
			if (current_action_ > 0)
			{
				--current_action_;
			}

		}
		else if (keycode == SDLK_DOWN)
		{
			if (current_action_ < 6)
			{
				++current_action_;
			}
		}
		else if (keycode == SDLK_RETURN)
		{
			Engine::stop_music();
			Engine::play_music("low.wav");
			std::this_thread::sleep_for(std::chrono::milliseconds(112));

			switch (current_action_) {
			case 0:
				Engine::stop_music();
				start_new_game();
				break;
			case 1:
				Engine::stop_music();
				scene_manager_->set_scene("load_game");
				scene_manager_->init();
				Engine::play_music("ingame.wav");
				break;
			case 2:
				Engine::stop_music();
				start_level_editor();
				break;
			case 3:
				Engine::stop_music();
				scene_manager_->set_scene("credits");
				Engine::play_music("credits.wav");
				break;
			case 4:
				Engine::stop_music();
				scene_manager_->set_scene("help");
				Engine::play_music("help.wav");
				break;
			case 5:
				Engine::stop_music();
				scene_manager_->set_scene("highscores");
				Engine::play_music("credits.wav");
				break;
			case 6:
				is_running_ = false;
				break;
			}
			
			if (!is_running_) {
				break;
			}
		}
	}
}

void MainMenu::start_new_game()
{
	auto core = new Core(scene_manager_);;
	scene_manager_->add_scene(core, true, "game");
	scene_manager_->set_scene("game");
	Engine::play_music("ingame.wav");
}

void MainMenu::start_level_editor()
{
	auto leveleditor = new LevelEditor(scene_manager_);
	scene_manager_->add_scene(leveleditor, true, "leveleditor");
	scene_manager_->set_scene("leveleditor");
	Engine::play_music("leveleditor.wav");
}

void MainMenu::cleanup()
{
	Engine::destroy_renderer();
	Engine::close_audio();
}

bool MainMenu::init()
{
	if (!Engine::init_renderer("Demonic Dungeon Castle", false, Constants::k_window_width, Constants::k_window_height)) {
		return false;
	}
	if (!Engine::init_audio()) {
		Engine::destroy_renderer();
		return false;
	}	
	auto credits = new Credits(scene_manager_);
	scene_manager_->add_scene(credits, true, "credits");
	
	auto help = new Help(scene_manager_);
	scene_manager_->add_scene(help, true, "help");

	auto load_game = new LoadGame(scene_manager_);
	scene_manager_->add_scene(load_game, true, "load_game");

	auto highscores = new Highscores(scene_manager_);
	scene_manager_->add_scene(highscores, true, "highscores");
	
	title_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle"));
	background_ = std::unique_ptr<Animation>(Engine::load_animation("mainmenu.png", 3));
	background_->scale = 1280.0 / 960.0;
	start_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Start game"));
	load_game_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Load game"));
	credits_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Credits"));
	help_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Help"));
	level_editor_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Level Editor"));
	quit_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, "Quit to desktop"));
	selector_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, ">"));
	highscore_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Highscores"));
	helper = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, {255, 255, 255, 255},
	                          "Use the arrow keys ^` to navigate the menu and press ENTER to confirm"));
	highscore_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Highscores"));
	Engine::play_music("mainmenu.wav");
	return true;
}

