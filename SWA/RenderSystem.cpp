#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
#include "TileComponent.h"
RenderSystem::RenderSystem(EntityManager* manager, TilemapComponent* tilemapcomponent) 
	: BaseSystem(manager) {
	tilemap_component = tilemapcomponent;
}

void RenderSystem::update(double dt)
{
	if (tilemap_component->reload) {
		tilemap_component->tilemap = Engine::LoadTileset(tilemap_component->path);
		tilemap_component->reload = false;
	}

	for (auto entityid : manager_->get_all_entities<AnimationComponent>()) {
		auto animation_component = manager_->get_component<AnimationComponent>(entityid);
		if (!animation_component.is_active) {
			//animation_component.animation = Engine::LoadAnimation(animation_component.filename);
			animation_component.is_active = true;
		}
		Engine::UpdateAnimation(&animation_component.animation);
	}

	for (auto entityid : manager_->get_all_entities<TileComponent>()) {
		auto tile_component = manager_->get_component<TileComponent>(entityid);

		Engine::RenderTile(
			tile_component.x_pos,
			tile_component.y_pos,
			tile_component.width,
			tile_component.height,
			tilemap_component->tiletypes[tile_component.tiletype][0],
			tilemap_component->tiletypes[tile_component.tiletype][1],
			tilemap_component->tilemap
		);
	}

}