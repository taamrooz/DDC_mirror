#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
#include "TileComponent.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "TileSetSingleton.h"
#include "RoomComponent.h"
#include "RoomSingleton.h"

RenderSystem::RenderSystem(EntityManager* manager) 
	: BaseSystem(manager) {
}

void RenderSystem::update(double dt)
{
	//Check if new tileset needs to be loaded
	if (TileSetSingleton::get_instance()->reload) {
		TileSetSingleton::get_instance()->tilemap = Engine::LoadTileset(TileSetSingleton::get_instance()->path);
		TileSetSingleton::get_instance()->reload = false;
	}

	//Render all tiles
	for (auto entityid : manager_->get_all_entities_from_current_room<TileComponent>()) {
		auto tile_component = manager_->get_component<TileComponent>(entityid);
		auto room_component = manager_->get_component<RoomComponent>(entityid);

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

	//Render all animations
	for (auto entityid : manager_->get_all_entities_from_current_room<AnimationComponent>()) {
		auto animation_component = manager_->get_component<AnimationComponent>(entityid);
		auto position_component = manager_->get_component<PositionComponent>(entityid);
		auto room_component = manager_->get_component<RoomComponent>(entityid);
		
		Engine::UpdateAnimation(&animation_component->animation, position_component->x, position_component->y, animation_component->flip_horizontally);
	}

	

}