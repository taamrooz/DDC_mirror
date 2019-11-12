#include "CollisionHandlers.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"
#include "ladderComponent.h"
#include "RoomSingleton.h"
#include "LadderComponent.h"

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
	auto ladder = manager->get_component<LadderComponent>(entity1);

	if (ladder != nullptr) {
		// load next level
		if (!RoomSingleton::get_instance()->reload_room) {
			RoomSingleton::get_instance()->current_room_index++;
			RoomSingleton::get_instance()->reload_room = true;
		}
	} else {

	}
	//stop player from moving into a wall

	//take damage if entity2 has damagecomponent

	//etc.
}