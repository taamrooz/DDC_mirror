#pragma once
#include <vector2d.h>
#include <EntityManager.h>

using namespace Engine;

vector2d Wander();
vector2d Seek(const int entity, vector2d TargetPos, EntityManager<Component>* manager);
vector2d Flee(const int entity, const int evader, EntityManager<Component>* manager);
vector2d Pursuit(const int entity, const int evader, EntityManager<Component>* manager);
vector2d WallAvoidance(const int entity, EntityManager<Component>* manager);
