#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
#include "TileComponent.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "TileSetSingleton.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"
#include "TextureComponent.h"
#include "DungeonSingleton.h"

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
		auto rect = Engine::rect2d(TileSetSingleton::get_instance()->tiletypes[tile_component->tiletype][0],
			TileSetSingleton::get_instance()->tiletypes[tile_component->tiletype][1],
			tile_component->width, tile_component->height);
		Engine::render_tile(
			tile_component->x_pos,
			tile_component->y_pos,
			rect,
			TileSetSingleton::get_instance()->tilemap
		);
	}

	//Render all animations
	for (auto entityid : manager_->get_all_entities_from_current_room<AnimationComponent>()) {
		auto animation_component = manager_->get_component<AnimationComponent>(entityid);
		auto position_component = manager_->get_component<PositionComponent>(entityid);
		if (animation_component->animations.find(animation_component->currentState) != animation_component->animations.end())
		{
			Engine::update_animation(animation_component->animations.at(animation_component->currentState).get(), position_component->x, position_component->y, animation_component->flip_horizontally);
		}
		else
		{
			Engine::update_animation(animation_component->animations.at(animation_component->animations.begin()->first).get(), position_component->x, position_component->y, animation_component->flip_horizontally);
		}
		if (animation_component->lock_until < Engine::get_ticks()) {
			animation_component->currentState = State::DEFAULT;
		}
	}

	for (auto entityid : manager_->get_all_entities_from_current_room<HealthComponent>())
	{
		auto character_component = manager_->get_component<CharacterComponent>(entityid);
		auto health_component = manager_->get_component<HealthComponent>(entityid);
		auto position_component = manager_->get_component<PositionComponent>(entityid);

		if (health_component->current_health < health_component->max_health) {
			bool friendly = character_component != nullptr;
			if (health_component->current_health <= 0) return;

			if (friendly) {
				Engine::set_render_draw_color(0, 255, 0, 255);
			}
			else {
				Engine::set_render_draw_color(255, 0, 0, 255);
			}

			// Healthbar outline
			int bar_length = 50;
			int bar_height = 10;
			Engine::rect2d health_bar_outline = { position_component->x, position_component->y - bar_height, bar_length, bar_height };
			Engine::draw_rectangle(health_bar_outline);

			// Current health
			float health_bar_length = (float)health_component->current_health / (float)health_component->max_health * (float)bar_length;
			Engine::rect2d health_bar = { position_component->x, position_component->y - bar_height, (int)health_bar_length, bar_height };
			Engine::fill_rectangle(health_bar);
		}
	}

	//Render inventory
	auto invId = manager_->get_all_entities<InventoryComponent>().front();
	auto inv = manager_->get_component<InventoryComponent>(invId);
	int x = 25;
	for (int i = 0; i < 10; i++) {
		int y = Engine::get_window_height() - 75;
		int scale = 3;
		if (i + 1 == inv->selected) {
			scale = 4;
			y -= 16;
		}
		Engine::set_render_draw_color(255, 255, 255, 100);
		Engine::rect2d rect = Engine::rect2d{ x, y, 16 * scale, 16 * scale };
		Engine::draw_rectangle(rect);
		Engine::fill_rectangle(rect);
		if (inv->items.size() > i) {
			auto texture = manager_->get_component<TextureComponent>(inv->items[i]);
			Engine::rect2d clip = Engine::rect2d{ 0, 0, 16 * scale, 16 * scale };
			auto t = texture->texture.get();
			Engine::render_texture(t, x, y, &clip);
		}
		x = x + (16 * scale);
	}

	//render minimap (placeholder until full dungeon gets loaded in)
	
	for (int i = 0; i < 5; ++i) {
		int x = 25 + (48 * i);
		for (int j = 0; j < 5; ++j) {
			int y = 25 + (48 * j);
			auto rect = Engine::rect2d(x, y, 48, 48);
			Engine::set_render_draw_color(52, 52, 52, 175);
			Engine::fill_rectangle(rect);
			Engine::draw_rectangle(rect);
			if (DungeonSingleton::get_instance()->has_room_at(i + j * 5)) {
				Engine::set_render_draw_color(80, 80, 80, 140);
				Engine::fill_rectangle(rect);
				Engine::set_render_draw_color(0, 0, 0, 200);
				Engine::draw_rectangle(rect);
				if (i + j * 5 == DungeonSingleton::get_instance()->get_current_room_number()) {
					Engine::set_render_draw_color(225, 225, 225, 175);
					Engine::draw_rectangle(rect);
				}
			}
		}
	}

	//render current level information
	std::string text = "Dungeon " + std::to_string(DungeonSingleton::get_instance()->get_current_level() + 1);
	level_hud = std::make_unique<Texture>(*Engine::load_text("manaspc.ttf", 50, { 0,255,0, 255 }, text.c_str()));
	Engine::render_texture(level_hud.get(), 550, 15, nullptr);
}