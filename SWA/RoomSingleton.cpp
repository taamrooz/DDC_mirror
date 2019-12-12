#include "RoomSingleton.h"
#include "DungeonSingleton.h"
#include <fstream>
#include <sstream>
#include "PositionComponent.h"
#include "ComponentFactory.h"
#include "CollisionComponent.h"
#include "TileComponent.h"
#include "Constants.h"

RoomSingleton::RoomSingleton() {
	reload_room = true;
}

RoomSingleton* RoomSingleton::instance = 0;

void RoomSingleton::load_map(Engine::EntityManager<Component>* manager, RoomComponent* room)
{
	auto path = room->room_name + Constants::k_map_suffix;
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
		for (int i = 0; i < Constants::k_total_tiles; ++i)
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
			if ((tileType >= 0) && (tileType < Constants::k_total_sprites))
			{
				std::vector<int> row(3);
				tiles.push_back(row);
				tiles[i][0] = x;
				tiles[i][1] = y;
				if (room != nullptr)
				{
					//up
					if (y <= Constants::k_tile_height * 2 && x >= 8 * Constants::k_tile_width && x <= 10 * Constants::k_tile_width && room->top != nullptr)
					{
						tiles[i][2] = 0;
					}
					//left
					else if (x == 0 && y >= 6 * Constants::k_tile_height && y <= 8 * Constants::k_tile_height && room->left != nullptr)
					{
						tiles[i][2] = 0;
					}
					//right
					else if (x == Constants::k_tile_width * 19 && y >= 6 * Constants::k_tile_height && y <= 8 * Constants::k_tile_height && room->right != nullptr)
					{
						tiles[i][2] = 0;
					}
					//down
					else if (y == Constants::k_tile_height * 14 && x >= 8 * Constants::k_tile_width && x <= 10 * Constants::k_tile_width && room->down != nullptr) {
						tiles[i][2] = 0;
					}
					else
					{
						tiles[i][2] = tileType;
					}
				}
				else
				{
					tiles[i][2] = tileType;
				}

			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				break;
			}



			//Move to next tile spot
			x += Constants::k_tile_width;

			//If we've gone too far
			if (x >= Constants::k_level_width)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += Constants::k_tile_height;
			}
		}
	}

	//Close the file
	map.close();

	for (auto& i : tiles) {
		auto room_component = std::make_unique<RoomComponent>(room->room_name, room->room_index);
		auto pos = std::make_unique<PositionComponent>(i[0], i[1]);
		auto tile = std::make_unique<TileComponent>(i[0], i[1], Constants::k_tile_width, Constants::k_tile_height, i[2]);
		auto id = manager->create_entity();
		manager->add_component_to_entity(id, std::move(pos));
		manager->add_component_to_entity(id, std::move(tile));
		manager->add_component_to_entity(id, std::move(room_component));
		for (unsigned int a = 0; a < sizeof(Constants::k_collision_tiles) / sizeof(Constants::k_collision_tiles[0]); a = a + 1) {
			if (Constants::k_collision_tiles[a] == i[2]) {
				auto coll = std::make_unique<CollisionComponent>(63, 63, nullptr);
				manager->add_component_to_entity(id, std::move(coll));
			}
		}
	}
}

void RoomSingleton::load_objects(Engine::EntityManager<Component>* manager, RoomComponent* room)
{
	//Get file path for object map
	auto object_path = room->room_name + Constants::k_object_suffix;
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

			auto id = manager->create_entity();
			auto room_comp = std::make_unique<RoomComponent>(room->room_name, room->room_index);
			manager->add_component_to_entity(id, std::move(room_comp));
			manager->add_component_to_entity(id, std::make_unique<PositionComponent>(x, y));
			ComponentFactory::get_instance()->CreateEntity(name, id, manager);
		}
	}
	objects.close();
}

RoomSingleton* RoomSingleton::get_instance()
{
	if (instance == nullptr) {
		instance = new RoomSingleton();
	}
	return instance;
}

void RoomSingleton::load_room(Engine::EntityManager<Component>* manager, RoomComponent* room)
{
	load_map(manager, room);
	load_objects(manager, room);
}
