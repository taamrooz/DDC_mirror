#pragma once
#include <vector2d.h>
#include <EntityManager.h>

vector2d Wander();
vector2d Seek(const int entity, vector2d TargetPos, Engine::EntityManager<Component>* manager);
vector2d Flee(const int entity, const int evader, Engine::EntityManager<Component>* manager);
vector2d Pursuit(const int entity, const int evader, Engine::EntityManager<Component>* manager);
