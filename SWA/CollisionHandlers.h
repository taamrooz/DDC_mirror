#pragma once
#include <cstdint>
#include "EntityManager.h"
#include "BaseSystem.h"
#include "DamagingComponent.h"
#include "HealthComponent.h"
#include "Core.h"

void DamageHandler(HealthComponent* health, DamagingComponent* dmg);
void BulletCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);
void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);
void ItemCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager);
void ChestCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager);
void EnemyBulletCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);
void UpdateVelocity(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);
