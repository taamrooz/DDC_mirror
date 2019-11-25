#include "AISystem.h"
#pragma once
#include "AIComponent.h"
#include "TileComponent.h"
#include <algorithm>
#include <Renderer.h>
#include "CharacterComponent.h"
#include "CollisionComponent.h"
#include <queue>
#include <map>

AISystem::AISystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager)
{}

void AISystem::update(double dt)
{
	
	for (auto entity : manager_->get_all_entities_from_current_room<AIComponent>()) {
		auto player = manager_->get_all_entities_from_current_room<CharacterComponent>().front();
		auto pPos = manager_->get_component<PositionComponent>(player);
		auto pColl = manager_->get_component<CollisionComponent>(player);

		auto pos = manager_->get_component<PositionComponent>(entity);
		auto vel = manager_->get_component<VelocityComponent>(entity);
		auto coll = manager_->get_component<CollisionComponent>(entity);
		auto tiles = manager_->get_all_entities_from_current_room<TileComponent>();
		int currentTile = 0;
		int playerTile = 0;
		for (auto i : tiles) {
			auto tile = manager_->get_component<TileComponent>(tiles[i]);
			if (pos->x + coll->width / 2 > tile->x_pos && pos->x + coll->width / 2 < tile->x_pos + tile->width && pos->y + coll->height / 2 > tile->y_pos && pos->y + coll->height / 2 < tile->y_pos + tile->height) {
				Engine::set_render_draw_color(0, 255, 0, 50);
				Engine::fill_rectangle(Engine::rect2d(tile->x_pos, tile->y_pos, tile->width, tile->height));
				currentTile = i;
			}
			if (pPos->x + pColl->width / 2 >= tile->x_pos && pPos->x + pColl->width / 2 <= tile->x_pos + tile->width && pPos->y + pColl->height / 2 >= tile->y_pos && pPos->y + pColl->height / 2 <= tile->y_pos + tile->height) {
				Engine::set_render_draw_color(0, 0, 255, 50);
				Engine::fill_rectangle(Engine::rect2d(tile->x_pos, tile->y_pos, tile->width, tile->height));
				playerTile = i;
			}
		}


		std::deque<int> queue;
		std::map<size_t, int> distances;
		std::deque<int> visited;
		std::map<int, int> costs;
		std::map<int, int> predecessors;

		for (std::size_t i = 0; i < tiles.size(); ++i) {
			costs.emplace(i, INT_MAX);
		}

		costs[currentTile] = 0;
		queue.push_back(0);
		distances.emplace(currentTile, 0);
		int i= 0;
		while (queue.size() > 0) {
			i++;
			int key = 0;
			for (auto& i : distances) {
				if (i.second == queue.front()) {
					key = i.first;
					break; // to stop searching
				}
			}

			auto nodeid = key;
			queue.pop_front();
			distances.erase(nodeid);
			visited.push_front(nodeid);
			auto tile = manager_->get_component<TileComponent>(nodeid);

			for (std::size_t i = 0; i < tile->adjecent_tiles.size(); ++i) {
				//calculate distance
				auto& to = tile->adjecent_tiles[i];
				auto toLocation = manager_->get_component<TileComponent>(to);
				Engine::set_render_draw_color(100, 100, 100, 100);
				Engine::fill_rectangle(Engine::rect2d(toLocation->x_pos, toLocation->y_pos, toLocation->width, toLocation->height));
				int distance = calculateDistance(pPos->x, toLocation->x_pos) + calculateDistance(pPos->y, toLocation->y_pos);
				int nodeDistance = calculateDistance(pPos->x, pos->x) + calculateDistance(pPos->x, pos->x);

				if (std::find(visited.begin(), visited.end(), to) == visited.end()) {

					queue.push_back(distance);
					distances[to] = distance;
				}
				
				if (costs[to] > costs[nodeid] + 1) {
					costs[to] = costs[nodeid] + 1;
					predecessors[to] = nodeid;
					if (to == playerTile) {
						queue.clear();
						break;
					}
				}

			}
			sort(queue.begin(), queue.end());
		}
		int current = playerTile;
		auto tileComp = manager_->get_component<TileComponent>(currentTile);
		while (true) {
			i++;
			if (current == currentTile) {
				break;
			}
			//g[current].tag(kmint::graph::node_tag::path);
			Engine::set_render_draw_color(255, 255, 0, 125);
			auto comp = manager_->get_component<TileComponent>(current);
			Engine::fill_rectangle(Engine::rect2d(comp->x_pos, comp->y_pos, comp->width, comp->height));
			if (predecessors[current] == currentTile) {
				for (std::size_t i = 0; i < tileComp->adjecent_tiles.size(); ++i) {
					if (tileComp->adjecent_tiles[i] == current) {
						vel->dx = tileComp->x_pos - comp->x_pos > 0 ? -2 : tileComp->x_pos - comp->x_pos == 0 ? 0 : 2;
						vel->dy = tileComp->y_pos - comp->y_pos > 0 ? -2 : tileComp->y_pos - comp->y_pos == 0 ? 0 : 2;
						break;
					}
				}
			}
			current = predecessors[current];
		}
	}
}

int AISystem::calculateDistance(int x1, int x2) {

	if (x1 - x2 < 0) {
		return (x1 - x2) * -1;
	}
	return x1 - x2;
}