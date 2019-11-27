#include "RoomSystem.h"
#include <fstream>
#include <sstream>
#include "TileComponent.h"
#include "RoomSingleton.h"
#include "PositionComponent.h"
#include "ComponentFactory.h"
#include "CollisionComponent.h"
#include "CollisionHandlers.h"
#include "RoomComponent.h"
#include "DamagingComponent.h"
#include "LevelSingleton.h"
#include <Audio.h>
#include "LevelBossComponent.h"

RoomSystem::RoomSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager)
{}

void RoomSystem::update(double dt)
{
	if (LevelSingleton::get_instance()->reload_level || RoomSingleton::get_instance()->reload_room) {
		// what to do when new level or room needs to be loaded?
		LoadTiles(RoomSingleton::get_instance()->get_current_room_name() + RoomSingleton::get_instance()->room_suffix, k_total_tiles_, k_total_sprites_, k_tile_width_, k_level_width_, k_tile_height_);
		LoadObjects();

		RoomSingleton::get_instance()->reload_room = false;
		LevelSingleton::get_instance()->reload_level = false;

		const auto boss_entities = manager_->get_all_entities_from_current_room<LevelBossComponent>();
		bool is_boss_room = !boss_entities.empty();

		if (is_boss_room) {
			Engine::stop_music();
			Engine::play_music("danger.wav");
		}
	}
}

void RoomSystem::LoadObjects() {
	//Get file path for object map
	auto object_path = RoomSingleton::get_instance()->get_current_room_name() + RoomSingleton::get_instance()->object_suffix;
	std::ifstream objects("./assets/Levels/" + object_path);

	if (objects.fail())
	{
		printf("Unable to load map file!\n");
	}
	else
	{
		std::string name;
		int x = -1, y = -1, count = 0;

		std::stringstream buffer;
		buffer << objects.rdbuf();

		while (buffer.peek() >= 0) {
			if (!(buffer >> name)) {
				std::cout << "Error!! First value is not a string" << std::endl;
				return;
			}
			if (!(buffer >> x)) {
				std::cout << "Error!! Second value is not an int" << std::endl;
				return;
			}
			if (!(buffer >> y)) {
				std::cout << "Error!! Third value is not an int" << std::endl;
				return;
			}

			auto id = manager_->create_entity();
			auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->get_current_room_name());
			manager_->add_component_to_entity(id, std::move(room));
			manager_->add_component_to_entity(id, std::make_unique<PositionComponent>(x, y));
			ComponentFactory::get_instance()->CreateEntity(name, id, manager_);
		}
	}
	objects.close();
}

void RoomSystem::LoadTiles(std::string path, int total_tiles, int total_sprites, int tile_width, int level_width, int tile_height)
{
	//tiles vector
	std::vector<std::vector<int>> tiles;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("./assets/Levels/" + path);

	//If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < total_tiles; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < total_sprites))
			{
				std::vector<int> row(3);
				tiles.push_back(row);
				tiles[i][0] = x;
				tiles[i][1] = y;
				tiles[i][2] = tileType;
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				break;
			}

			//Move to next tile spot
			x += tile_width;

			//If we've gone too far
			if (x >= level_width)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += tile_height;
			}
		}
	}

	//Close the file
	map.close();

	for (std::vector<int> i : tiles) {
		auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->get_current_room_name());
		auto pos = std::make_unique<PositionComponent>(i[0], i[1]);
		auto tile = std::make_unique<TileComponent>(i[0], i[1], tile_width, tile_height, i[2]);
		auto id = manager_->create_entity();
		manager_->add_component_to_entity(id, std::move(pos));
		manager_->add_component_to_entity(id, std::move(tile));
		manager_->add_component_to_entity(id, std::move(room));
		for (unsigned int a = 0; a < sizeof(k_collision_tiles) / sizeof(k_collision_tiles[0]); a = a + 1) {
			if (k_collision_tiles[a] == i[2]) {
				auto coll = std::make_unique<CollisionComponent>(63, 63, nullptr);
				manager_->add_component_to_entity(id, std::move(coll));
			}
		}
	}

}