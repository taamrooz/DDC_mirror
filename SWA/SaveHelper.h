#pragma once
#include "EntityManager.h"

class SaveHelper
{
public:
	void SaveGameToFile(Engine::EntityManager<Component>* manager_, std::string path);
	void LoadGameFromFile(Engine::EntityManager<Component>* manager_, std::string path);
};

