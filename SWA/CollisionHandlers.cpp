#include "CollisionHandlers.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"
#include "DoorComponent.h"
#include "RoomSingleton.h"

void BulletCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager)
{
	auto player = manager->get_component<CharacterComponent>(entity2);
	if (player == nullptr) {
		manager->remove_entity(entity1);
	}
}

void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager)
{
	auto player = manager->get_component<CharacterComponent>(entity2);
	auto door = manager->get_component<DoorComponent>(entity1);

	if (door != nullptr) {
		// load next level
		RoomSingleton::get_instance()->current_room_index++;
		RoomSingleton::get_instance()->reload_room = true;
	} else {

	}
	//stop player from moving into a wall

	//take damage if entity2 has damagecomponent

	//etc.
}