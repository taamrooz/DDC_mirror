#include "Core.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "Credits.h"
#include "EndGameWin.h"
#include "EndGameLose.h"
#include "Help.h"
#include "Pause.h"
#include "LevelEditor.h"
#include "JsonHelper.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#undef main

void init_scenes()
{
	auto sm = std::make_unique<Engine::SceneManager>();
	auto mm = new MainMenu(sm.get());	
	sm->add_scene(mm, true, "mainmenu");	
	sm->set_scene("mainmenu");
	sm->render();
	sm->cleanup();
}
int main(int argc, char* argv[])
{
	init_scenes();
	_CrtDumpMemoryLeaks();
	return 0;
}