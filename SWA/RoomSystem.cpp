#include "RoomSystem.h"
#include <fstream>
#include "TileComponent.h"
#include "RoomSingleton.h"

RoomSystem::RoomSystem(EntityManager* manager) : BaseSystem(manager)
{}

void RoomSystem::update(double dt)
{
	if (RoomSingleton::get_instance()->reload_room) {
		LoadTiles(RoomSingleton::get_instance()->room_path, 192, 12, 80, 1280, 80);
		RoomSingleton::get_instance()->reload_room = false;
	}
}

void RoomSystem::LoadTiles(std::string path, int total_tiles, int total_sprites, int tile_width, int level_width, int tile_height)
{
	//Success flag
	bool tilesLoaded = true;

	//tiles vector
	std::vector<std::vector<int>> tiles;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("./assets/"+path);

	//If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
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
				tilesLoaded = false;
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
				tilesLoaded = false;
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
		auto component = std::make_unique<TileComponent>(i[0],i[1],80,80,i[2]);
		auto id = manager_->create_entity();
		manager_->add_component_to_entity(id, std::move(component));
	}

}