#include "LoadGame.h"
#include <filesystem>
#include <UserInput.h>

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
			//scene_manager_->set_scene("mainmenu");
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
			std::string filename = entry.path().filename().string();
			file_names_.emplace_back(filename);
			file_name_textures_.push_back(std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, filename.c_str())));
		}
	}
}

void LoadGame::input_load_game(SDL_Keycode keycode, std::string& text)
{
	if (keycode == SDLK_BACKSPACE && text_.length() > 0)
		load_game_file_name_.pop_back();
	if (keycode == SDLK_RETURN)
		// open load_game_file_name_
	load_game_file_name_.append(text);
}

void LoadGame::render() {
	const auto timer = Engine::pre_update();

	get_files("./assets/Levels", "map");
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