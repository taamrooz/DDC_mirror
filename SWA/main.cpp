#include "Core.h"
#include "SceneManager.h"
#include "MainMenu.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include "stdlib.h"
#include "crtdbg.h"
#undef main
#endif

void register_menus()
{
	auto sm = std::make_unique<SceneManager>();
	auto mm = std::make_unique<MainMenu>(sm.get());
	mm->init();
	sm->add_scene(std::move(mm));
	sm->render();
	sm->cleanup();
}
int main(int argc, char* argv[])
{
	register_menus();
	_CrtDumpMemoryLeaks();
	return 0;
}