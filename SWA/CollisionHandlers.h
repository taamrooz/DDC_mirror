#pragma once
#include <cstdint>
#include "EntityManager.h"

void BulletCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager);
void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager);
void ChestCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager);