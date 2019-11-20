#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
#include "TileComponent.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "TileSetSingleton.h"
#include "RoomComponent.h"
#include "RoomSingleton.h"
#include "DamagingComponent.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"
#include "TextureComponent.h"

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
		if(animation_component->animations.find(animation_component->currentState) != animation_component->animations.end())
		{
			Engine::UpdateAnimation(&animation_component->animations.at(animation_component->currentState), position_component->x, position_component->y, animation_component->flip_horizontally);
		}else
		{
			Engine::UpdateAnimation(&animation_component->animations.at(animation_component->animations.begin()->first), position_component->x, position_component->y, animation_component->flip_horizontally);
		}
		if (animation_component->lock_until < Engine::GetTicks()) {
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
			Engine::RenderHealthBar(position_component->x, position_component->y, friendly, health_component->max_health, health_component->current_health);
		}
	}

	//Render inventory
	auto invId = manager_->get_all_entities_from_current_room<InventoryComponent>().front();
	auto inv = manager_->get_component<InventoryComponent>(invId);
	int x = 25;
	for (int i = 0; i < 10; i++) {
		bool selected = false;
		if (i + 1 == inv->selected) {
			selected = true;
		}
		Engine::RenderInventoryTile(selected, x);
		if (inv->items.size() > i) {
			auto texture = manager_->get_component<TextureComponent>(inv->items[i]);
			Engine::RenderInventoryItem(texture->path, selected, x);
		}
		x = x + (16 * 3);
		if (selected) {
			x += 16;
		}
	}	

	//render minimap (placeholder until full dungeon gets loaded in)
	Engine::ClearRectangles();
	for (int i = 0; i < 5; i++) {
		int x = 25 + (48 * (i));
		for (int j = 0; j < 5; j++) {
			int y = 25 + (48 * j);
			Engine::AddRectangle(x, y, 48, 48);
			Engine::FillRectangles(50, 50, 50, 150);
			Engine::RenderRectangles(0, 0, 0, 175);
			if (i == 2 && j == 2) {
				Engine::RenderEmptyTile(x, y, 96, 96);
			}
		}
	}
}