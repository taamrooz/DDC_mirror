#include "MainMenu.h"
#include "Audio.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Core.h"

MainMenu::~MainMenu() = default;

MainMenu::MainMenu(SceneManager * manager) : BaseScene(manager) {}
void MainMenu::render()
{
	Engine::RenderClear();
	auto user_inputs = Engine::GetInputs();
	if (!user_inputs.second) {
		is_running = false;
		return;
	}
	for (const auto& keycode : user_inputs.first)
	{
		if(keycode == SDLK_q)
		{
			scene_manager_->pop_menu();
		}else if(keycode == SDLK_g)
		{
			auto* core = new Core(scene_manager_);
			core->init();
			scene_manager_->push_menu(*core);
			//delete core;
		}
	}
	title->render(50, 50, nullptr);
	Engine::Render();
	
}

void MainMenu::cleanup()
{
	Engine::DestroyRenderer();
	Engine::CloseAudio();
}

bool MainMenu::init()
{
	if (!Engine::InitRenderer("Demonic Dungeon Crawler", false, 800, 600)) {
		return false;
	}
	if (!Engine::InitAudio()) {
		return false;
	}
	title = Engine::LoadText("vgafix.fon", 20, { 0,0,0 }, "Demonic Dungeon Crawler");
	return true;
}

