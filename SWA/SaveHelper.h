#pragma once
#include "EntityManager.h"

class SaveHelper
{
public:
	void SaveGameToFile(Engine::EntityManager<Component>* manager_);
};

