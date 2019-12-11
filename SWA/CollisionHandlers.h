#pragma once
#include <cstdint>
#include "EntityManager.h"
#include "BaseSystem.h"
#include "DamagingComponent.h"
#include "HealthComponent.h"
#include "EnemyComponent.h"
#include "Core.h"
enum class CollisionHandlerNames
{
	None,
	BulletCollisionHandler,
	PlayerCollisionHandler,
	ItemCollisionHandler,
	ChestCollisionHandler,
	EnemyCollisionHandler,
	UpdateVelocity
};

void DamageHandler(HealthComponent* health, DamagingComponent* dmg, EnemyComponent* enemy);
void BulletCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);
void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);
void ItemCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);
void ChestCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);
void EnemyCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);
void UpdateVelocity(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core);

class CollisionHandlers
{
private:
	std::unordered_map<CollisionHandlerNames, std::function<void(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component> * manager, Core * core)>> name_function_map_;
public:
	CollisionHandlers();
	std::function<void(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component> * manager, Core * core)> GetFunction(CollisionHandlerNames name);
};