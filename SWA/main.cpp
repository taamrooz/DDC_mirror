#include "Core.h"
#include "SceneManager.h"
#include "MainMenu.h"
#ifdef _DEBUG
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
	mm->init();
	core->init();
	sm->add_scene(*mm);
	sm->add_scene(*core);
	sm->render();
	sm->cleanup();
	core.release();
	mm.release();
	sm.release();
	_CrtDumpMemoryLeaks();
	return 0;
}