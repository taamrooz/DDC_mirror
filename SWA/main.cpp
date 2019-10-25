#include "Core.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "Credits.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include "stdlib.h"
#include "crtdbg.h"
#undef main
#endif
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char* argv[])
{
	auto sm = std::make_unique<SceneManager>();
	auto mm = std::make_unique<MainMenu>(sm.get());
	auto core = std::make_unique<Core>(sm.get());
	auto credits = std::make_unique<Credits>(sm.get());
	mm->init();
	core->init();
	credits->init();

	sm->add_scene(*mm);
	sm->add_scene(*core);
	sm->add_scene(*credits);

	sm->render();
	sm->cleanup();
	core.release();
	mm.release();
	sm.release();
	_CrtDumpMemoryLeaks();
	return 0;
}