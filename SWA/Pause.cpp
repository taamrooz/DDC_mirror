#include "Pause.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"

Pause::~Pause() = default;

Pause::Pause(Engine::SceneManager* manager) : BaseScene(manager) { }

void Pause::render()
{
	const auto timer = Engine::pre_update();
	input();
	Engine::update_animation(background_.get(), 0, 0);
	Engine::render_texture(title_.get(), 250, 200, nullptr);
	Engine::render_texture(paused_texture_.get(), 550, 400, nullptr);
	Engine::render_texture(helper_.get(), 475, 600, nullptr);
	Engine::render(timer);
}

void Pause::input() {
	const int k_keydown = 0;

	auto inputs = Engine::GetInputs();

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_p)
		{
			Engine::resume_music();
			scene_manager_->set_scene("game");
			break;
		}
	}
}

void Pause::cleanup() { }

bool Pause::init() {
	title_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle"));
	paused_texture_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 50, { 255,196,0,255 }, "PAUSED"));
	helper_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 }, "Press P to continue ..."));
	background_ = std::make_unique<Animation>(*Engine::load_animation("mainmenu.png", 3));
	background_->scale = 1280.0 / 960.0;
	return true;
}