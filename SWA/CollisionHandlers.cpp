#include "CollisionHandlers.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"

void BulletCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager)
{
	auto player = manager->get_component<CharacterComponent>(entity2);
	if (player == nullptr) {
		manager->remove_entity(entity1);
	}
}

void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager)
{
	//stop player from moving into a wall

	//take damage if entity2 has damagecomponent

	//etc.
}
