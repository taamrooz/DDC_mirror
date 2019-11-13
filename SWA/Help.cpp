#include "Help.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"

Help::~Help() = default;

Help::Help(SceneManager* manager) : BaseScene(manager) { }

void Help::render()
{
	const auto timer = Engine::PreUpdate();
	input();
	Engine::UpdateAnimation(background_, 0, 0);
	Engine::RenderTexture(title_, 250, 200, nullptr);
	Engine::RenderTexture(sub_title_moving_, 100, 300, nullptr);
	Engine::RenderTexture(sub_title_shooting_, 750, 300, nullptr);
	Engine::RenderTexture(move_up_, 100, 400, nullptr);
	Engine::RenderTexture(move_left_, 100, 450, nullptr);
	Engine::RenderTexture(move_right_, 100, 500, nullptr);
	Engine::RenderTexture(move_down_, 100, 550, nullptr);
	Engine::RenderTexture(shoot_up_, 750, 400, nullptr);
	Engine::RenderTexture(shoot_left_, 750, 450, nullptr);
	Engine::RenderTexture(shoot_right_, 750, 500, nullptr);
	Engine::RenderTexture(shoot_down_, 750, 550, nullptr);
	Engine::RenderTexture(helper, 370, 750, nullptr);
	Engine::Render(timer);
}

void Help::input() {
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

void Help::cleanup() {
	title_->free_texture();
	sub_title_moving_->free_texture();
	sub_title_shooting_->free_texture();
	move_up_->free_texture();
	move_left_->free_texture();
	move_right_->free_texture();
	move_down_->free_texture();
	shoot_up_->free_texture();
	shoot_left_->free_texture();
	shoot_right_->free_texture();
	shoot_down_->free_texture();
	helper->free_texture();
	Engine::DestroyRenderer();
	Engine::CloseAudio();
}

bool Help::init() {
	title_ = Engine::LoadText("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle");
	sub_title_moving_ = Engine::LoadText("manaspc.ttf", 40, { 255,0,0, 255 }, "Moving controls");
	sub_title_shooting_ = Engine::LoadText("manaspc.ttf", 40, { 255,0,0, 255 }, "Shooting controls");
	background_ = &Engine::LoadAnimation("mainmenu.png", 3);
	background_->scale = 1280.0 / 960.0;
	move_up_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 },		("Move up:        " + KeyBindingSingleton::get_instance()->get_move_up_key()).c_str());
	move_left_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 },		("Move left:      " + KeyBindingSingleton::get_instance()->get_move_left_key()).c_str());
	move_right_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 },	("Move right:     " + KeyBindingSingleton::get_instance()->get_move_right_key()).c_str());
	move_down_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 },		("Move down:      " + KeyBindingSingleton::get_instance()->get_move_down_key()).c_str());
	shoot_up_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 },		("Shoot up:       " + KeyBindingSingleton::get_instance()->get_shoot_up_key()).c_str());
	shoot_left_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 },	("Shoot left:     " + KeyBindingSingleton::get_instance()->get_shoot_left_key()).c_str());
	shoot_right_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 },	("Shoot right:    " + KeyBindingSingleton::get_instance()->get_shoot_right_key()).c_str());
	shoot_down_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 },	("Shoot down:     " + KeyBindingSingleton::get_instance()->get_shoot_down_key()).c_str());
	helper = Engine::LoadText("manaspc.ttf", 24, { 255, 255, 255, 255 }, "Press ENTER to quit to main menu");
	return true;
}