#pragma once
#include <string>
#include "Component.h"
struct RoomComponent;

namespace Engine {
	template<typename T> class EntityManager;
}

class RoomSingleton
{
private:
	static RoomSingleton* instance;
	RoomSingleton();	
	int current_room_index;
	void load_map(Engine::EntityManager<Component>* manager, RoomComponent* room);
	void load_objects(Engine::EntityManager<Component>* manager);
	//Constants for the drawing of tiles
	constexpr static int k_level_width_ = 1280;
	constexpr static int k_total_tiles_ = 300;
	constexpr static int k_tile_height_ = 64;
	constexpr static int k_tile_width_ = 64;
	constexpr static int k_total_sprites_ = 49;
	constexpr static int k_collision_tiles[37] = { 2, 3, 4, 5 ,6 ,9 ,11 ,12 , 13 ,16, 17, 18 ,19 ,20 ,23 ,24 , 25 ,26 ,27 ,30 ,31 ,32 ,33 ,34, 36 ,37 ,38 ,39 ,40, 41, 42, 43, 44, 45, 46, 47, 48 };
public:
	//If reload_room is true, load the map from at the room_path location
	bool reload_room;
	static RoomSingleton* get_instance();
	std::string get_current_room_name();
	std::string object_suffix;
	std::string room_suffix;
	void init_first_room();
	void init_next_room();
	void load_room(Engine::EntityManager<Component>* manager, RoomComponent* room);
};
