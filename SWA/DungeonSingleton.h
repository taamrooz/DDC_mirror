#pragma once
#include <string>
#include <vector>
#include "RoomComponent.h"
#include <map>
#include <memory>
#include "EntityManager.h"

class DungeonSingleton
{
private:
	static DungeonSingleton* instance;
	DungeonSingleton();
	uint8_t current_room_{0};
	uint32_t current_level_{0};
	std::vector<std::unique_ptr<RoomComponent>> level_rooms_;
	std::vector<std::string> levels_;
public:
	void load_dungeon(const std::string& path, Engine::EntityManager<Component>* manager);
	void load_all_dungeons(Engine::EntityManager<Component>* manager, bool new_game);
	void move_room(Direction dir);
	void move_room_up();
	void move_room_right();
	void move_room_down();
	void move_room_left();
	void load_room(Engine::EntityManager<Component>* manager);
	void load_all_objects(Engine::EntityManager<Component>* manager);
	void move_dungeon_down(Engine::EntityManager<Component>* manager);
	bool skip_until_dungeon(const std::string& path, Engine::EntityManager<Component>* manager);
	void set_current_room_number(int room_number);
	static DungeonSingleton* get_instance();
	RoomComponent* get_current_room() const;
	std::string get_current_level_path() const;
	uint32_t get_current_level() const;
	uint8_t get_starting_room();
	uint8_t get_current_room_number() const;
	bool is_last_dungeon() const;
	bool has_room_at(int index) const;
	void delete_instance();
};
