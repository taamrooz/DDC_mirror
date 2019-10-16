#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
#include "TileComponent.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "TileSetSingleton.h"

RenderSystem::RenderSystem(EntityManager* manager) 
	: BaseSystem(manager) {
}

void RenderSystem::update(double dt)
{
	if (TileSetSingleton::get_instance()->reload) {
		TileSetSingleton::get_instance()->tilemap = Engine::LoadTileset(TileSetSingleton::get_instance()->path);
		TileSetSingleton::get_instance()->reload = false;
	}

	for (auto entityid : manager_->get_all_entities<TileComponent>()) {
		auto tile_component = manager_->get_component<TileComponent>(entityid);

		Engine::RenderTile(
			tile_component->x_pos,
			tile_component->y_pos,
			tile_component->width,
			tile_component->height,
			TileSetSingleton::get_instance()->tiletypes[tile_component->tiletype][0],
			TileSetSingleton::get_instance()->tiletypes[tile_component->tiletype][1],
			TileSetSingleton::get_instance()->tilemap
		);
	}

	for (auto entityid : manager_->get_all_entities<AnimationComponent>()) {
		auto animation_component = manager_->get_component<AnimationComponent>(entityid);
		auto position_component = manager_->get_component<PositionComponent>(entityid);

		bool should_flip_horizontally = false;

		Engine::UpdateAnimation(&animation_component->animation, position_component->x, position_component->y, should_flip_horizontally);
	}

	

}