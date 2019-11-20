#include "EndGameLose.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"

EndGameLose::~EndGameLose() = default;

EndGameLose::EndGameLose(Engine::SceneManager * manager) : BaseScene(manager) { }

void EndGameLose::render()
{
	const auto timer = Engine::pre_update();
	input();
	Engine::update_animation(background_.get(), 0, 0);
	Engine::render_texture(title_.get(), 400, 400, nullptr);
	Engine::render_texture(sub_title_.get(), 230, 500, nullptr);
	Engine::render_texture(helper_.get(), 370, 750, nullptr);
	Engine::render(timer);
}

void EndGameLose::input() {
	const int k_keydown = 0;

	auto inputs = Engine::GetInputs();

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_RETURN)
		{
			scene_manager_->pop_scene().pop_scene().pop_scene();
			break;
		}
	}
}

void EndGameLose::cleanup() {
}

bool EndGameLose::init() {
	title_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "You didnt make it."));
	sub_title_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 40, { 255,196,0,255 }, "LOSER LOSER DOUBLE LOSER :p!"));
	background_ = std::unique_ptr<Animation>(Engine::load_animation("mainmenu.png", 3));
	background_->scale = 1280.0 / 960.0;
	helper_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 },
		"Press ENTER to quit to main menu"));
	return true;
}