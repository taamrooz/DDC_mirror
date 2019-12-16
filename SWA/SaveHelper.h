#pragma once
#include "EntityManager.h"

class Core;

class SaveHelper
{
public:
	void SaveGameToFile(Engine::EntityManager<Component>* manager_, std::string path, int timer_state);
	bool LoadGameFromFile(Engine::EntityManager<Component>* manager_, std::string path, Core* core);
};

