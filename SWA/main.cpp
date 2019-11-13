#include "Core.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "LevelEditor.h"
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
	auto level_edit = std::make_unique<LevelEditor>(sm.get());
	mm->init();
	core->init();
	level_edit->init();
	sm->add_scene(*mm);
	sm->add_scene(*core);
	sm->add_scene(*level_edit);
	sm->render();
	sm->cleanup();
	core.release();
	mm.release();
	level_edit.release();
	sm.release();
	_CrtDumpMemoryLeaks();
	return 0;
}