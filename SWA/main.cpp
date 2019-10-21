#include "Core.h"
#include "SceneManager.h"
#include "MainMenu.h"
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
	mm->init();
	sm->add_scene(*mm);
	sm->render();
	sm->cleanup();
	mm.release();
	sm.release();
	_CrtDumpMemoryLeaks();
	return 0;
}