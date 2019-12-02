#include "CheatSystem.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "KeyBindingSingleton.h"
#include "HealthComponent.h"

CheatSystem::CheatSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager)
{
}

void CheatSystem::update(double dt)
{
	auto entities = manager_->get_all_entities_from_current_room<CharacterComponent>();
	if (entities.empty()) return;
	auto entity = entities.front();
	auto health = manager_->get_component<HealthComponent>(entity);
	auto velocity = manager_->get_component<VelocityComponent>(entity);
	auto position = manager_->get_component<PositionComponent>(entity);
	bool move_up, move_right, move_down;
	bool move_left = (move_up = move_right = move_down = false);
	for (auto& i : KeyBindingSingleton::get_instance()->keys_down)
	{
		if (i.second) {
			if (i.first == KeyBindingSingleton::get_instance()->get_move_up_key_binding()) {
				move_up = true;
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_move_left_key_binding()) {
				move_left = true;
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_move_down_key_binding()) {
				move_down = true;
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_move_right_key_binding()) {
				move_right = true;
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_speedhack_key()) {
				if (move_left) velocity->dx -= 10;
				if (move_up) velocity->dy -= 10;
				if (move_right) velocity->dx += 10;
				if (move_down) velocity->dy += 10;
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_invincible_key())
			{
				health->current_health = health->max_health;
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_teleport_key())
			{
				if (move_left) position->x -= 50;
				if (move_up) position->y -= 50;
				if (move_right) position->x += 50;
				if (move_down) position->y += 50;
			}
			else if(i.first == KeyBindingSingleton::get_instance()->get_next_room_key())
			{
				RoomSingleton::get_instance()->init_next_room();
				RoomSingleton::get_instance()->reload_room = true;
			}
		}
	}
}
