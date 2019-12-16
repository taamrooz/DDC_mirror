#include "Highscores.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"
#include <Audio.h>
#include <mutex>

Highscores::Highscores(Engine::SceneManager* manager) : BaseScene(manager) { }

void Highscores::render()
{
	int emplacement = 270;
	const auto timer = Engine::pre_update();
	input();
	Engine::update_animation(background_.get(), 0, 0);
	Engine::render_texture(title_.get(), 250, 125, nullptr);
	Engine::render_texture(highscore_.get(), 490, 200, nullptr);
	Engine::render_texture(explanation_.get(), 490, 245, nullptr);
	Engine::render_texture(helper_.get(), 370, 850, nullptr);
	for (auto& highscoreTexture : highscore_textures_)
	{
		Engine::render_texture(highscoreTexture.get(), 490, emplacement, nullptr);
		emplacement += 25;
	}

	Engine::render(timer);
}

void Highscores::input() {
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
			scene_manager_->set_scene("mainmenu");
			Engine::play_music("mainmenu.wav");
			break;
		}
		if (keycode == SDLK_c)
		{
			scene_manager_->set_scene("cheats");
		}
	}
}

void Highscores::cleanup() { }

bool Highscores::init() {
	title_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle"));
	background_ = std::unique_ptr<Animation>(Engine::load_animation("mainmenu.png", 3));
	helper_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 }, "Press ENTER to quit to main menu"));
	highscore_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 40, { 255, 196, 0, 255 }, "Highscores"));
	explanation_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, "Date | Achieved Time"));
	background_->scale = 1280.0 / 960.0;
	get_highscores();
	return true;
}

void Highscores::get_highscores()
{
	highscore_textures_ = std::vector<std::unique_ptr<Texture>>();
	std::string highscoreString;
	std::string highscorePath = "./assets/Highscores/highscores";
	auto json = Engine::get_json();
	Engine::read_from_file(json, highscorePath);

	for (json::iterator it = json.begin(); it != json.end(); ++it)
	{

		if (it.value().find("Date") != it.value().end()) {
			highscoreString =  it.value().find("Date").value();
			highscoreString += " ";
		}
		if (it.value().find("Time") != it.value().end()) {
			highscoreString += it.value().find("Time").value();
		}
		highscore_textures_.push_back(std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, highscoreString.c_str())));
	}
}