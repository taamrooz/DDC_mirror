#pragma once
#include <cstdint>
#include "EntityManager.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"
#include "DamagingComponent.h"
#include "HealthComponent.h"
#include <Renderer.h>
#include "AnimationComponent.h"
#include "Core.h"

void DamageHandler(HealthComponent* health, DamagingComponent* dmg);
void BulletCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager, Core* core);
void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager, Core* core);
void EnemyBulletCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager, Core* core);
void UpdateVelocity(uint32_t entity1, uint32_t entity2, EntityManager* manager, Core* core);