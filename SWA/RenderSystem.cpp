#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
#include "TileComponent.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "TileSetSingleton.h"
#include "RoomComponent.h"
#include "HealthComponent.h"

RenderSystem::RenderSystem(Engine::EntityManager<Component>* manager)
	: BaseSystem(manager) {
}

void RenderSystem::update(double dt)
{
	//Check if new tileset needs to be loaded
	if (TileSetSingleton::get_instance()->reload) {
		TileSetSingleton::get_instance()->tilemap = Engine::load_tileset(TileSetSingleton::get_instance()->path);
		TileSetSingleton::get_instance()->reload = false;
	}

	//Render all tiles
	for (auto entityid : manager_->get_all_entities_from_current_room<TileComponent>()) {
		auto tile_component = manager_->get_component<TileComponent>(entityid);
		auto room_component = manager_->get_component<RoomComponent>(entityid);

		Engine::render_tile(
			tile_component->x_pos,
			tile_component->y_pos,
			tile_component->width,
			tile_component->height,
			TileSetSingleton::get_instance()->tiletypes[tile_component->tiletype][0],
			TileSetSingleton::get_instance()->tiletypes[tile_component->tiletype][1],
			TileSetSingleton::get_instance()->tilemap
		);
	}

	//Render all animations
	for (auto entityid : manager_->get_all_entities_from_current_room<AnimationComponent>()) {
		auto animation_component = manager_->get_component<AnimationComponent>(entityid);
		auto position_component = manager_->get_component<PositionComponent>(entityid);
		if(animation_component->animations.find(animation_component->currentState) != animation_component->animations.end())
		{
			Engine::update_animation(&animation_component->animations.at(animation_component->currentState), position_component->x, position_component->y, animation_component->flip_horizontally);
		}else
		{
			Engine::update_animation(&animation_component->animations.at(animation_component->animations.begin()->first), position_component->x, position_component->y, animation_component->flip_horizontally);
		}
		if (animation_component->lock_until < Engine::get_ticks()) {
			animation_component->currentState = State::DEFAULT;
		}
	}

	for (auto entityid : manager_->get_all_entities<HealthComponent>())
	{
		auto character_component = manager_->get_component<CharacterComponent>(entityid);
		auto health_component = manager_->get_component<HealthComponent>(entityid);
		auto position_component = manager_->get_component<PositionComponent>(entityid);

		if (health_component->current_health < health_component->max_health) {
			bool friendly = character_component != nullptr;
			Engine::render_health_bar(position_component->x, position_component->y, friendly, health_component->max_health, health_component->current_health);
		}
	}
}