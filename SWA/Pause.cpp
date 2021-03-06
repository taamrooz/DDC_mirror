#include "Pause.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"

Pause::~Pause() = default;

Pause::Pause(Engine::SceneManager * manager, Core * core) : BaseScene(manager), core_ { core } { }

void Pause::render()
{	
	const auto timer = Engine::pre_update();
	input();	
	Engine::update_animation(background_.get(), 0, 0);
	if (save_text_.length() > 0)
	{
		text_texture_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, save_text_.c_str()));
	}
	if (save_text_.length() > 0)
		Engine::render_texture(text_texture_.get(), 450, 800, nullptr);
	Engine::render_texture(title_.get(), 250, 200, nullptr);
	Engine::render_texture(paused_texture_.get(), 550, 400, nullptr);
	Engine::render_texture(helper_.get(), 450, 600, nullptr);
	Engine::render_texture(helper2_.get(), 190, 700, nullptr);
	Engine::render(timer);
}

void Pause::input() {
	const int k_keydown = 0;
	const int k_stop = 2;
	const int k_text = 3;

	auto inputs = Engine::GetInputs();
	if (!std::get<k_stop>(inputs)) {
		is_running_ = false;
		return;
	}
	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		auto text = std::get<k_text>(inputs);
		
		if (keycode == SDLK_BACKSPACE && save_text_.length() > 0)
			save_text_.pop_back();
		if (keycode == SDLK_RETURN){
			core_->save_game(save_text_);
			save_text_.clear();
		}
		
		save_text_.append(text);
		if (keycode == SDLK_TAB)
		{
			Engine::resume_music();
			scene_manager_->set_scene("game");
			core_->unpause_timer();
			break;
		}
	}
}

void Pause::cleanup() { }

bool Pause::init() {
	title_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle"));
	paused_texture_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 50, { 255,196,0,255 }, "PAUSED"));
	helper_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 }, "Press TAB to continue..."));
	helper2_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 }, "Type the name for your savegame and press RETURN to save"));
	background_ = std::unique_ptr<Animation>(Engine::load_animation("mainmenu.png", 3));
	background_->scale = 1280.0 / 960.0;
	Engine::StartTextInput();
	return true;
}