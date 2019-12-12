#include "Help.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"
#include "KeyBindingSingleton.h"
#include <Audio.h>
#include <mutex>
#include "CheatScene.h"

Help::Help(Engine::SceneManager* manager) : BaseScene(manager) { }

void Help::render()
{
	const auto timer = Engine::pre_update();
	input();
	Engine::update_animation(background_.get(), 0, 0);
	Engine::render_texture(title_.get(), 250, 125, nullptr);
	Engine::render_texture(instructions_first_line.get(), 50, 200, nullptr);
	Engine::render_texture(instructions_second_line.get(), 50, 250, nullptr);
	Engine::render_texture(instructions_third_line.get(), 50, 300, nullptr);
	Engine::render_texture(sub_title_moving_.get(), 100, 375, nullptr);
	Engine::render_texture(sub_title_shooting_.get(), 750, 375, nullptr);
	Engine::render_texture(move_up_.get(), 100, 425, nullptr);
	Engine::render_texture(move_left_.get(), 100, 475, nullptr);
	Engine::render_texture(move_right_.get(), 100, 525, nullptr);
	Engine::render_texture(move_down_.get(), 100, 575, nullptr);
	Engine::render_texture(shoot_up_.get(), 750, 425, nullptr);
	Engine::render_texture(shoot_left_.get(), 750, 475, nullptr);
	Engine::render_texture(shoot_right_.get(), 750, 525, nullptr);
	Engine::render_texture(shoot_down_.get(), 750, 575, nullptr);
	Engine::render_texture(sub_title_in_game_controls_.get(), 400, 650, nullptr);
	Engine::render_texture(pause_.get(), 420, 700, nullptr);
	Engine::render_texture(quit_.get(), 420, 750, nullptr);

	Engine::render_texture(helper.get(), 370, 850, nullptr);
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
			Engine::stop_music();
			Engine::play_music("low.wav");
			std::this_thread::sleep_for(std::chrono::milliseconds(112));

			Engine::stop_music();
			scene_manager_->set_scene("mainmenu");
			Engine::play_music("mainmenu.wav");
			break;
		}
		if(keycode == SDLK_c)
		{
			scene_manager_->set_scene("cheats");
		}
	}
}

void Help::cleanup() { }

bool Help::init() {
	auto cheats = new CheatScene(scene_manager_);
	scene_manager_->add_scene(cheats, true, "cheats");
	title_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Castle"));
	sub_title_moving_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 40, { 255,0,0, 255 }, "Moving controls"));
	sub_title_shooting_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 40, { 255,0,0, 255 }, "Shooting controls"));
	background_ = std::unique_ptr<Animation>(Engine::load_animation("mainmenu.png", 3));
	background_->scale = 1280.0 / 960.0;
	move_up_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },		("Move up:        " + KeyBindingSingleton::get_instance()->get_move_up_key()).c_str()));
	move_left_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },		("Move left:      " + KeyBindingSingleton::get_instance()->get_move_left_key()).c_str()));
	move_right_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },	("Move right:     " + KeyBindingSingleton::get_instance()->get_move_right_key()).c_str()));
	move_down_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },		("Move down:      " + KeyBindingSingleton::get_instance()->get_move_down_key()).c_str()));
	shoot_up_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },		("Shoot up:       " + KeyBindingSingleton::get_instance()->get_shoot_up_key()).c_str()));
	shoot_left_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },	("Shoot left:     " + KeyBindingSingleton::get_instance()->get_shoot_left_key()).c_str()));
	shoot_right_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },	("Shoot right:    " + KeyBindingSingleton::get_instance()->get_shoot_right_key()).c_str()));
	shoot_down_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 },	("Shoot down:     " + KeyBindingSingleton::get_instance()->get_shoot_down_key()).c_str()));
	helper = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 255, 255, 255 }, "Press ENTER to quit to main menu"));
	instructions_first_line = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Walk through the rooms, kill the enemies, pick up the elixirs or mysterious"));
	instructions_second_line = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, " objects from the treasure chests and head to the last rooms of the levels"));
	instructions_third_line = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255, 196, 0, 255 }, "                       to kill the level bosses!"));
	sub_title_in_game_controls_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 40, { 255,0,0, 255 }, "In game controls"));
	pause_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, ("Pause game:        P")));
	quit_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 24, { 255,196,0,255 }, ("Quit game:         Q")));
	return true;
}