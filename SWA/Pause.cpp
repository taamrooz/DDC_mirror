#include "Pause.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"

Pause::~Pause() = default;

Pause::Pause(SceneManager* manager) : BaseScene(manager) { }

void Pause::render()
{
	const auto timer = Engine::PreUpdate();
	input();
	Engine::UpdateAnimation(background_, 0, 0);
	Engine::RenderTexture(title_, 250, 200, nullptr);
	Engine::Render(timer);
}

void Pause::input() {
	const int k_keydown = 0;
	const int k_stop = 2;

	auto inputs = Engine::GetInputs();

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_RETURN || keycode == SDLK_p)
		{
			scene_manager_->pop_scene();
			scene_manager_->pop_scene();
			scene_manager_->pop_scene();
			scene_manager_->render();
			break;
		}
	}
}

void Pause::cleanup() {
	delete background_;
	delete title_;
	Engine::DestroyRenderer();
	Engine::CloseAudio();
}

bool Pause::init() {
	title_ = Engine::LoadText("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle");
	background_ = &Engine::LoadAnimation("mainmenu.png", 3);
	background_->scale = 1280.0 / 960.0;
	return true;
}