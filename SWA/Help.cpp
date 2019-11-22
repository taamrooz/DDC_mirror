#include "Help.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"

Help::~Help() = default;

Help::Help(Engine::SceneManager* manager) : BaseScene(manager) { }

void Help::render()
{
	const auto timer = Engine::pre_update();
	input();
	Engine::update_animation(background_.get(), 0, 0);
	Engine::render_texture(title_.get(), 250, 200, nullptr);
	Engine::render_texture(sub_title_moving_.get(), 100, 300, nullptr);
	Engine::render_texture(sub_title_shooting_.get(), 750, 300, nullptr);
	Engine::render_texture(move_up_.get(), 100, 400, nullptr);
	Engine::render_texture(move_left_.get(), 100, 450, nullptr);
	Engine::render_texture(move_right_.get(), 100, 500, nullptr);
	Engine::render_texture(move_down_.get(), 100, 550, nullptr);
	Engine::render_texture(shoot_up_.get(), 750, 400, nullptr);
	Engine::render_texture(shoot_left_.get(), 750, 450, nullptr);
	Engine::render_texture(shoot_right_.get(), 750, 500, nullptr);
	Engine::render_texture(shoot_down_.get(), 750, 550, nullptr);
	Engine::render_texture(helper.get(), 370, 750, nullptr);
	Engine::render(timer);
}

void Help::input() {
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
			scene_manager_->set_scene("mainmenu");
			break;
		}
	}
}

void Help::cleanup() { }

bool Help::init() {
	title_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle"));
	sub_title_moving_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 40, { 255,0,0, 255 }, "Moving controls"));
	sub_title_shooting_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 40, { 255,0,0, 255 }, "Shooting controls"));
	background_ = std::make_unique<Animation>(*Engine::load_animation("mainmenu.png", 3));
	background_->scale = 1280.0 / 960.0;
	move_up_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },		("Move up:        " + KeyBindingSingleton::get_instance()->get_move_up_key()).c_str()));
	move_left_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },		("Move left:      " + KeyBindingSingleton::get_instance()->get_move_left_key()).c_str()));
	move_right_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },	("Move right:     " + KeyBindingSingleton::get_instance()->get_move_right_key()).c_str()));
	move_down_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },		("Move down:      " + KeyBindingSingleton::get_instance()->get_move_down_key()).c_str()));
	shoot_up_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },		("Shoot up:       " + KeyBindingSingleton::get_instance()->get_shoot_up_key()).c_str()));
	shoot_left_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },	("Shoot left:     " + KeyBindingSingleton::get_instance()->get_shoot_left_key()).c_str()));
	shoot_right_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },	("Shoot right:    " + KeyBindingSingleton::get_instance()->get_shoot_right_key()).c_str()));
	shoot_down_ = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },	("Shoot down:     " + KeyBindingSingleton::get_instance()->get_shoot_down_key()).c_str()));
	helper = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 }, "Press ENTER to quit to main menu"));
	return true;
}