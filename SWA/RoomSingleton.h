#pragma once
#include <string>
#include "Component.h"
struct RoomComponent;

namespace Engine {
	template<typename T> class EntityManager;
}

enum Direction
{
	none,
	up,
	down,
	left,
	right
};

class RoomSingleton
{
private:
	static RoomSingleton* instance;
	RoomSingleton();
	void load_map(Engine::EntityManager<Component>* manager, RoomComponent* room);
	void load_objects(Engine::EntityManager<Component>* manager, RoomComponent* room);
public:
	//If reload_room is true, load the map from at the room_path location
	bool reload_room;
	Direction dir;
	static RoomSingleton* get_instance();
	void load_room(Engine::EntityManager<Component>* manager, RoomComponent* room);
	void delete_instance();
};
