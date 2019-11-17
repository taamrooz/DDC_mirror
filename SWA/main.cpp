#include "Core.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "Credits.h"
#include "Help.h"
#include "Pause.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#undef main
#endif


void init_scenes()
{
	auto sm = std::make_unique<Engine::SceneManager>();
	auto mm = new MainMenu(sm.get());
	auto core = new Core(sm.get());
	auto credits = new Credits(sm.get());
	auto help = new Help(sm.get());
	auto pause = new Pause(sm.get());
	sm->add_scene(mm, true);
	sm->add_scene(core, true);
	sm->add_scene(credits, true);
	sm->add_scene(help, true);
	sm->add_scene(pause, true);

	sm->render();
	sm->cleanup();
}
int main(int argc, char* argv[])
{
	init_scenes();
	_CrtDumpMemoryLeaks();
	return 0;
}