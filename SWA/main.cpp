#include "SceneManager.h"
#include "MainMenu.h"
#include <Windows.h>
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
#ifdef _DEBUG
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#else
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
	init_scenes();
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}