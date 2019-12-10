#include "Core.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "Credits.h"
#include "EndGameWin.h"
#include "EndGameLose.h"
#include "LoadGame.h"
#include "Help.h"
#include "Pause.h"
#include "LevelEditor.h"
#include "CheatScene.h"
#include "Highscores.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#undef main

void init_scenes()
{
	auto sm = std::make_unique<Engine::SceneManager>();
	auto mm = new MainMenu(sm.get());
	auto core = new Core(sm.get());
	auto level = new LevelEditor(sm.get());
	auto credits = new Credits(sm.get());
	auto help = new Help(sm.get());
	auto pause = new Pause(sm.get());
	auto endgamewin = new EndGameWin(sm.get());
	auto endgamelose = new EndGameLose(sm.get());
	auto cheats = new CheatScene(sm.get());
	auto load_game = new LoadGame(sm.get());
	auto highscores = new Highscores(sm.get());
	sm->add_scene(mm, true, "mainmenu");
	sm->add_scene(core, false, "game");
	sm->add_scene(level, true, "leveleditor");
	sm->add_scene(credits, true, "credits");
	sm->add_scene(help, true, "help");
	sm->add_scene(pause, true, "pause");
	sm->add_scene(endgamewin, true, "win");
	sm->add_scene(endgamelose, true, "lose");
	sm->add_scene(cheats, true, "cheats");
	sm->add_scene(load_game, true, "load_game");
	sm->add_scene(highscores, true, "highscores");
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