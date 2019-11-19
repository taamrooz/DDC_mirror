#include "Core.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "Credits.h"
#include "EndGame.h"
#include "Help.h"
#include "Pause.h"
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
	auto credits = std::make_unique<Credits>(sm.get());
	auto help = std::make_unique<Help>(sm.get());
	auto pause = std::make_unique<Pause>(sm.get());
	auto level_edit = std::make_unique<LevelEditor>(sm.get());
	auto endgame = std::make_unique<EndGame>(sm.get());
	mm->init();
	core->init();
	credits->init();
	help->init();
	pause->init();
	endgame->init();

	level_edit->init();
	sm->add_scene(*mm);
	sm->add_scene(*core);
	sm->add_scene(*level_edit);
	sm->add_scene(*credits);
	sm->add_scene(*help);
	sm->add_scene(*pause);
	sm->add_scene(*endgame);

	sm->render();
	sm->cleanup();
	core.release();
	mm.release();
	level_edit.release();
	sm.release();
	_CrtDumpMemoryLeaks();
	return 0;
}