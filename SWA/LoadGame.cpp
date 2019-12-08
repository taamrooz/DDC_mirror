#include "LoadGame.h"
#include <filesystem>
#include <UserInput.h>
#include <mutex>
#include "Core.h"
#include <Audio.h>
#include <fstream> 

LoadGame::~LoadGame() = default;

LoadGame::LoadGame(Engine::SceneManager* manager) : BaseScene(manager) { }

void LoadGame::cleanup() {

}

void LoadGame::input()
{
	const int k_keydown = 0;
	const int k_stop = 2;
	const int k_text = 3;

	auto inputs = Engine::GetInputs();

	if (!std::get<k_stop>(inputs)) {
		Engine::StopTextInput();
		//is_running_ = false;
		return;
	}

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_ESCAPE)
		{
			Engine::stop_music();
			Engine::play_music("low.wav");
			std::this_thread::sleep_for(std::chrono::milliseconds(112));
			Engine::stop_music();
			scene_manager_->set_scene("mainmenu");
			Engine::play_music("mainmenu.wav");
		}

		input_load_game(keycode, std::get<k_text>(inputs));
	}
}

void LoadGame::get_files(const char* path, const std::string extension)
{
	file_name_textures_.clear();
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (entry.path().extension().string() == "." + extension)
		{
			std::string file_name = entry.path().filename().string();
			file_name = file_name.substr(0, file_name.size() - 5);
			file_names_.emplace_back(file_name);
			file_name_textures_.push_back(std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, file_name.c_str())));
		}
	}
}

void LoadGame::input_load_game(SDL_Keycode keycode, std::string& text)
{
	if (keycode == SDLK_BACKSPACE && text_.length() > 0)
		text_.pop_back();
	if (keycode == SDLK_RETURN)
		if (open_game_file(text_))
		{
			Engine::StopTextInput();

			// TO-DO: switch scenemaneger to game scene with currently loaded game! (Other Userstory)
			Engine::stop_music();
			scene_manager_->set_scene("game");
			Engine::play_music("ingame.wav");
		}
	text_.append(text);
}

bool LoadGame::open_game_file(std::string& path) {
	std::ifstream game("./assets/Levels/" + path);
	if (game.fail())
	{
		return false;
	}
	
	// TO-DO: write logic of loading game here! (Other Userstory)

	return true;
}

void LoadGame::render() {
	const auto timer = Engine::pre_update();

	get_files("./assets/Levels", "json");
	if (text_.length() > 0)
	{
		text_texture_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, text_.c_str()));
	}
	int x = 100;
	int y = 50;
	for (auto& file : file_name_textures_)
	{
		Engine::render_texture(file.get(), x, y, nullptr);
		x += 400;
		if (x > 950)
		{
			x = 100;
			y += 50;
		}
	}
	if (text_.length() > 0)
		Engine::render_texture(text_texture_.get(), 450, 800, nullptr);


	Engine::render(timer);
	input();
}

bool LoadGame::init() {

	return true;
}