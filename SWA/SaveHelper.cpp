#include "SaveHelper.h"
#include "AnimationComponent.h"
#include "LoadGame.h"
#include "PositionComponent.h"
#include "CharacterComponent.h"
#include "ChestComponent.h"
#include "CollectableHandlers.h"
#include "CollectableComponent.h"
#include "CollisionHandlers.h"
#include "CollisionComponent.h"
#include "InventoryComponent.h"
#include "LadderComponent.h"
#include "LevelBossComponent.h"
#include "ShootingComponent.h"
#include "SteeringComponent.h"
#include "TextureComponent.h"
#include "VelocityComponent.h"
#include "TileComponent.h"

void SaveHelper::SaveGameToFile(Engine::EntityManager<Component>* manager_, std::string path)
{
	auto json = Engine::get_json();
	auto entities = manager_->get_all_entities();

	for (auto entity : entities)
	{

		auto components = manager_->get_all_components_from_entity(entity);
		for (auto c : components)
		{
			c->ToJson(json, entity);
		}
	}

	json["DungeonSingleton"]["current_room_number"] = DungeonSingleton::get_instance()->get_current_room_number();
	json["DungeonSingleton"]["level_path"] = DungeonSingleton::get_instance()->get_current_level_path();

	Engine::write_to_file(json, "assets/json/" + path);
}

bool SaveHelper::LoadGameFromFile(Engine::EntityManager<Component>* manager_, std::string path)
{
	auto json = Engine::get_json();
	Engine::read_from_file(json, path);

	/*
	 *it.key() = Entity ID
	 *it.value() = All the things contained in the entity
	 */

	auto current_level_name = DungeonSingleton::get_instance();

	for (json::iterator it = json.begin(); it != json.end(); ++it)
	{

		if (it.key() == "DungeonSingleton")
		{
			auto current_room_number = it.value().find("current_room_number").value();
			auto level_path = it.value().find("level_path").value();
			if (!DungeonSingleton::get_instance()->skip_until_dungeon(level_path))
			{
				return false;
			}
			DungeonSingleton::get_instance()->set_current_room_number(current_room_number);
		}
		else {
			auto new_entity = manager_->create_entity();

			//Animation Component:
			if (it.value().find("AnimationComponent") != it.value().end())
			{
				std::unordered_map<State, std::string> state_to_path;
				std::unordered_map<State, int> state_to_frames;
				std::unordered_map<State, std::unique_ptr<Animation>> animations;

				auto animation_component = it.value().find("AnimationComponent").value();

				//Member variables:
				auto currentState = animation_component.find("currentState").value();
				auto flip_horizontally = animation_component.find("flip_horizontally").value();
				auto visible = animation_component.find("visible").value();

				//States:
				auto states = animation_component.find("states").value();
				if (states.find("DEFAULT") != states.end()) {
					auto default_state = states.find("DEFAULT").value();
					state_to_path.try_emplace(State::DEFAULT, default_state.find("path").value());
					state_to_frames.try_emplace(State::DEFAULT, default_state.find("frames").value());
					animations.emplace(std::make_pair<State,
						std::unique_ptr<Animation>>(State::DEFAULT,
							std::unique_ptr<Animation>(Engine::load_animation(state_to_path.at(State::DEFAULT), state_to_frames.at(State::DEFAULT)))));
					animations.find(State::DEFAULT)->second->scale = default_state.find("scale").value();
					animations.find(State::DEFAULT)->second->pause = default_state.find("pause").value();
				}
				if (states.find("HIT") != states.end()) {
					auto hit_state = states.find("HIT").value();
					state_to_path.try_emplace(State::HIT, hit_state.find("path").value());
					state_to_frames.try_emplace(State::HIT, hit_state.find("frames").value());
					animations.emplace(std::make_pair<State,
						std::unique_ptr<Animation>>(State::HIT,
							std::unique_ptr<Animation>(Engine::load_animation(state_to_path.at(State::HIT), state_to_frames.at(State::HIT)))));
					animations.find(State::HIT)->second->scale = hit_state.find("scale").value();
					animations.find(State::HIT)->second->pause = hit_state.find("pause").value();
				}
				if (states.find("RUN") != states.end()) {
					auto run_state = states.find("RUN").value();
					state_to_path.try_emplace(State::RUN, run_state.find("path").value());
					state_to_frames.try_emplace(State::RUN, run_state.find("frames").value());
					animations.emplace(std::make_pair<State,
						std::unique_ptr<Animation>>(State::RUN,
							std::unique_ptr<Animation>(Engine::load_animation(state_to_path.at(State::RUN), state_to_frames.at(State::RUN)))));
					animations.find(State::RUN)->second->scale = run_state.find("scale").value();
					animations.find(State::RUN)->second->pause = run_state.find("pause").value();
				}

				//Component creation
				auto ani = std::make_unique<AnimationComponent>(animations, state_to_path, state_to_frames);
				ani->currentState = currentState;
				ani->flip_horizontally = flip_horizontally;
				ani->lock_until = 0;
				ani->visible = visible;

				manager_->add_component_to_entity(new_entity, std::move(ani));
			}
			//Character Component
			if (it.value().find("CharacterComponent") != it.value().end())
			{
				auto cha = std::make_unique<CharacterComponent>();

				manager_->add_component_to_entity(new_entity, std::move(cha));
			}
			//Chest Component
			if (it.value().find("ChestComponent") != it.value().end())
			{
				auto contains = it.value().find("ChestComponent").value().find("contains").value();
				auto che = std::make_unique<ChestComponent>(contains);

				manager_->add_component_to_entity(new_entity, std::move(che));
			}
			//Collectable Component
			if (it.value().find("CollectableComponent") != it.value().end())
			{
				auto function_name = it.value().find("CollectableComponent").value().find("function_name").value();
				auto function = CollectableHandlers{}.GetFunction(function_name);
				auto collect = std::make_unique<CollectableComponent>(function_name, function);

				manager_->add_component_to_entity(new_entity, std::move(collect));
			}
			//Collision Component
			if (it.value().find("CollisionComponent") != it.value().end())
			{
				auto collision_component = it.value().find("CollisionComponent").value();

				auto width = collision_component.find("width").value();
				auto height = collision_component.find("height").value();
				auto solid = collision_component.find("solid").value();
				auto function_name = collision_component.find("function_name").value();
				auto function = CollisionHandlers{}.GetFunction(static_cast<CollisionHandlerNames>(function_name));

				auto coll = std::make_unique<CollisionComponent>(width, height, function, function_name, solid);

				manager_->add_component_to_entity(new_entity, std::move(coll));
			}
			//Damaging Component
			if (it.value().find("DamagingComponent") != it.value().end())
			{
				auto damaging_component = it.value().find("DamagingComponent").value();

				auto damage_amount = damaging_component.find("damage_amount").value();
				auto remove_entity_on_damage = damaging_component.find("remove_entity_on_damage").value();

				auto dmg = std::make_unique<DamagingComponent>(damage_amount, remove_entity_on_damage);

				manager_->add_component_to_entity(new_entity, std::move(dmg));
			}
			//Enemy Component
			if (it.value().find("EnemyComponent") != it.value().end())
			{
				auto enemy_component = it.value().find("EnemyComponent").value();

				auto mass = enemy_component.find("mass").value();
				auto state = enemy_component.find("state").value();

				auto enemy = std::make_unique<EnemyComponent>();
				enemy->mass = mass;
				enemy->state = state;

				manager_->add_component_to_entity(new_entity, std::move(enemy));
			}
			//Health Component
			if (it.value().find("HealthComponent") != it.value().end())
			{
				auto health_component = it.value().find("HealthComponent").value();

				auto current_health = health_component.find("current_health").value();
				auto max_health = health_component.find("max_health").value();
				auto time_invulnerable = health_component.find("time_invulnerable").value();

				auto health = std::make_unique<HealthComponent>(current_health, max_health, time_invulnerable);

				manager_->add_component_to_entity(new_entity, std::move(health));
			}
			//Ladder Component
			if (it.value().find("LadderComponent") != it.value().end())
			{
				auto ladder = std::make_unique<LadderComponent>();

				manager_->add_component_to_entity(new_entity, std::move(ladder));
			}
			//Level Boss Component
			if (it.value().find("LevelBossComponent") != it.value().end())
			{
				auto boss = std::make_unique<LevelBossComponent>();

				manager_->add_component_to_entity(new_entity, std::move(boss));
			}
			//Position Component
			if (it.value().find("PositionComponent") != it.value().end())
			{
				auto pos = std::make_unique<PositionComponent>(
					it.value().find("PositionComponent").value().find("x").value(),
					it.value().find("PositionComponent").value().find("y").value()
					);

				manager_->add_component_to_entity(new_entity, std::move(pos));
			}
			//Room Component
			if (it.value().find("RoomComponent") != it.value().end())
			{
				auto room = std::make_unique<RoomComponent>(
					it.value().find("RoomComponent").value().find("room_name").value(),
					it.value().find("RoomComponent").value().find("room_index").value()
					);

				manager_->add_component_to_entity(new_entity, std::move(room));
			}
			//Shooting Component
			if (it.value().find("ShootingComponent") != it.value().end())
			{
				auto shooting_component = it.value().find("ShootingComponent").value();

				auto bullet_size = shooting_component.find("bullet_size").value();
				auto fire_rate = shooting_component.find("fire_rate").value();
				auto bullet_shape = shooting_component.find("bullet_shape").value();

				auto shoot = std::make_unique<ShootingComponent>(bullet_size, fire_rate, bullet_shape);

				manager_->add_component_to_entity(new_entity, std::move(shoot));
			}
			//Steering Component
			if (it.value().find("SteeringComponent") != it.value().end())
			{
				auto steering_component = it.value().find("SteeringComponent").value();

				auto steer = std::make_unique<SteeringComponent>();

				steer->m_dWanderDistance = steering_component.find("m_dWanderDistance").value();
				steer->m_dWanderJitter = steering_component.find("m_dWanderJitter").value();
				steer->m_dWanderRadius = steering_component.find("m_dWanderRadius").value();

				manager_->add_component_to_entity(new_entity, std::move(steer));
			}
			//Texture Component
			if (it.value().find("TextureComponent") != it.value().end())
			{
				auto texture_component = it.value().find("TextureComponent").value();

				auto path = texture_component.find("path").value();
				//auto texture = std::unique_ptr<Engine::load_tileset>;
				auto texture = std::make_unique<TextureComponent>(std::unique_ptr<Texture>(Engine::load_tileset(path)), path);

				manager_->add_component_to_entity(new_entity, std::move(texture));
			}
			//Tile Component
			if (it.value().find("TileComponent") != it.value().end())
			{
				auto tile_component = it.value().find("TileComponent").value();

				auto x_pos = tile_component.find("x_pos").value();
				auto y_pos = tile_component.find("y_pos").value();
				auto width = tile_component.find("width").value();
				auto height = tile_component.find("height").value();
				auto tiletype = tile_component.find("tiletype").value();

				auto tile = std::make_unique<TileComponent>(x_pos, y_pos, width, height, tiletype);

				manager_->add_component_to_entity(new_entity, std::move(tile));
			}
			//Velocity Component
			if (it.value().find("VelocityComponent") != it.value().end())
			{
				auto velocity_component = it.value().find("VelocityComponent").value();

				auto dx = velocity_component.find("dx").value();
				auto dy = velocity_component.find("dy").value();
				auto dropOff = velocity_component.find("dropOff").value();
				auto deceleration = velocity_component.find("deceleration").value();
				auto maxSpeed = velocity_component.find("maxSpeed").value();

				auto vel = std::make_unique<VelocityComponent>(dx, dy, dropOff);
				vel->deceleration = deceleration;
				vel->maxSpeed = maxSpeed;

				manager_->add_component_to_entity(new_entity, std::move(vel));
			}
		}
	}
	
	//Inventory Component
	auto inv = std::make_unique<InventoryComponent>();

	std::vector<uint32_t> items{};
	auto texture_c = manager_->get_all_entities<TextureComponent>();
	auto collec_c = manager_->get_all_entities<CollectableComponent>();

	for (auto c : collec_c)
	{
		if(std::find(texture_c.begin(), texture_c.end(), c) != texture_c.end())
		{
			items.emplace_back(c);
		}
	}
	inv->items = items;
	inv->selected = 1;

	manager_->add_component_to_entity(manager_->get_all_entities<CharacterComponent>().front(), std::move(inv));
	
	return true;
}
