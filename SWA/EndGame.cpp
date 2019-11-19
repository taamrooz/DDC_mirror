#include "EndGame.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"

EndGame::~EndGame() = default;

EndGame::EndGame(SceneManager * manager) : BaseScene(manager) { }

void EndGame::render()
{
	const auto timer = Engine::PreUpdate();
	input();
	Engine::UpdateAnimation(background_, 0, 0);
	Engine::RenderTexture(title_, 400, 400, nullptr);
	Engine::RenderTexture(sub_title_, 230, 500, nullptr);
	Engine::RenderTexture(helper, 370, 750, nullptr);
	Engine::Render(timer);
}

void EndGame::input() {
	const int k_keydown = 0;
	const int k_stop = 2;

	auto inputs = Engine::GetInputs();

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_RETURN)
		{
			is_running = false;
			scene_manager_->pop_scene();
			scene_manager_->pop_scene();
			scene_manager_->pop_scene();
			break;
		}
	}
}

void EndGame::cleanup() {
	delete background_;
	delete title_;
	delete sub_title_;
	delete helper;
	Engine::DestroyRenderer();
	Engine::CloseAudio();
}

bool EndGame::init() {
	title_ = Engine::LoadText("manaspc.ttf", 50, { 255,0,0, 255 }, "Congratz mate!");
	sub_title_ = Engine::LoadText("manaspc.ttf", 40, { 255,196,0,255 }, "WINNER WINNER CHICKEN DINNER!");
	background_ = &Engine::LoadAnimation("mainmenu.png", 3);
	background_->scale = 1280.0 / 960.0;
	helper = Engine::LoadText("manaspc.ttf", 24, { 255, 255, 255, 255 },
		"Press ENTER to quit to main menu");
	return true;
}