#include "MainMenu.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"

MainMenu::~MainMenu() = default;

MainMenu::MainMenu(SceneManager * manager) : BaseScene(manager) { }

void MainMenu::render()
{
	Engine::RenderClear();
	input();
	Engine::UpdateAnimation(background_, 0, 0);
	title_->render(250, 200, nullptr);
	start_->render(400, 300, nullptr);
	settings_->render(400, 400, nullptr);
	quit_->render(400, 500, nullptr);
	Engine::Render();
	
}

void MainMenu::input()
{
	auto user_inputs = Engine::GetInputs();
	if (!user_inputs.second) {
		is_running = false;
		return;
	}
	for (const auto& keycode : user_inputs.first)
	{
		if (keycode == SDLK_q)
		{
			scene_manager_->pop_scene();
		}
		else if (keycode == SDLK_g)
		{
			scene_manager_->push_scene();
		}
	}
}


void MainMenu::cleanup()
{
	Engine::DestroyRenderer();
	Engine::CloseAudio();
}

bool MainMenu::init()
{
	if (!Engine::InitRenderer("Demonic Dungeon Crawler", false, 1280, 960)) {
		return false;
	}
	if (!Engine::InitAudio()) {
		return false;
	}
	title_ = Engine::LoadText("manaspc.ttf", 50, { 255,0,0, 255 }, "Demonic Dungeon Crawler");
	background_ = &Engine::LoadAnimation("mainmenu.png", 3);
	start_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Start game");
	settings_ = Engine::LoadText("manaspc.ttf", 24, { 255, 196, 0, 255 }, "Settings");
	quit_ = Engine::LoadText("manaspc.ttf", 24, { 255,196,0,255 }, "Quit to desktop");
	return true;
}

