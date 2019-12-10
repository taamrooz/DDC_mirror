#include "RoomSingleton.h"
#include "LevelSingleton.h"
#include <fstream>
#include <sstream>
#include "PositionComponent.h"
#include "ComponentFactory.h"
#include "CollisionComponent.h"
#include "TileComponent.h"

RoomSingleton::RoomSingleton() {
	reload_room = true;
	current_room_index = 0;
	room_suffix = ".map";
	object_suffix = ".objects";
}

RoomSingleton* RoomSingleton::instance = 0;

void RoomSingleton::load_map(Engine::EntityManager<Component>* manager, RoomComponent* room)
{
	auto path = room->room_name + get_instance()->room_suffix;
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
		for (int i = 0; i < k_total_tiles_; ++i)
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
			if ((tileType >= 0) && (tileType < k_total_sprites_))
			{
				std::vector<int> row(3);
				tiles.push_back(row);
				tiles[i][0] = x;
				tiles[i][1] = y;
				if (room != nullptr)
				{
					//up
					if (y <= k_tile_height_ * 2 && x >= 7 * k_tile_width_ && x <= 11 * k_tile_width_ && room->top != nullptr)
					{
						tiles[i][2] = 0;
					}
					//left
					else if (x == 0 && y >= 6 * k_tile_height_ && y <= 8 * k_tile_height_ && room->left != nullptr)
					{
						tiles[i][2] = 0;
					}
					//right
					else if (x == k_tile_width_ * 19 && y >= 6 * k_tile_height_ && y <= 8 * k_tile_height_ && room->right != nullptr)
					{
						tiles[i][2] = 0;
					}
					//down
					else if (y == k_tile_height_ * 14 && x >= 7 * k_tile_width_ && x <= 11 * k_tile_width_ && room->down != nullptr) {
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
			x += k_tile_width_;

			//If we've gone too far
			if (x >= k_level_width_)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += k_tile_height_;
			}
		}
	}

	//Close the file
	map.close();

	for (auto& i : tiles) {
		auto room_component = std::make_unique<RoomComponent>(get_current_room_name(), LevelSingleton::get_instance()->get_current_room_number());
		auto pos = std::make_unique<PositionComponent>(i[0], i[1]);
		auto tile = std::make_unique<TileComponent>(i[0], i[1], k_tile_width_, k_tile_height_, i[2]);
		auto id = manager->create_entity();
		manager->add_component_to_entity(id, std::move(pos));
		manager->add_component_to_entity(id, std::move(tile));
		manager->add_component_to_entity(id, std::move(room_component));
		for (unsigned int a = 0; a < sizeof(k_collision_tiles) / sizeof(k_collision_tiles[0]); a = a + 1) {
			if (k_collision_tiles[a] == i[2]) {
				auto coll = std::make_unique<CollisionComponent>(63, 63, nullptr);
				manager->add_component_to_entity(id, std::move(coll));
			}
		}
	}
}

void RoomSingleton::load_objects(Engine::EntityManager<Component>* manager)
{
	//Get file path for object map
	auto object_path = get_current_room_name() + object_suffix;
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
			auto room = std::make_unique<RoomComponent>(get_current_room_name(), LevelSingleton::get_instance()->get_current_room_number());
			manager->add_component_to_entity(id, std::move(room));
			manager->add_component_to_entity(id, std::make_unique<PositionComponent>(x, y));
			ComponentFactory::get_instance()->CreateEntity(name, id, manager);
		}
	}
	objects.close();
}

RoomSingleton* RoomSingleton::get_instance()
{
	if (instance == 0) {
		instance = new RoomSingleton();
	}
	return instance;
}

std::string RoomSingleton::get_current_room_name() {
	return LevelSingleton::get_instance()->get_current_room_name_from_current_level();
}

void RoomSingleton::init_first_room() {
	current_room_index = 0;
}

void RoomSingleton::init_next_room() {
	current_room_index++;
}

void RoomSingleton::load_room(Engine::EntityManager<Component>* manager, RoomComponent* room)
{
	load_map(manager, room);
	load_objects(manager);
}
