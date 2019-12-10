#pragma once
#include <string>
#include <vector>
#include "RoomComponent.h"
#include <map>
#include <memory>
#include "EntityManager.h"

class LevelSingleton
{
private:
	static LevelSingleton* instance;
	LevelSingleton();
	uint8_t current_room_{0};
	uint8_t starting_room_;
	std::string current_level_;
	std::string levels[3][3] = { "lazy", "second", "third", "two_first", "two_second", "two_third", "third_first", "third_second", "third_third" };
	std::map<std::string, std::vector<std::unique_ptr<RoomComponent>>> level_rooms_;
public:
	void load_dungeon(const std::string& path);
	void load_all_dungeons();
	void move_room_up();
	void move_room_right();
	void move_room_down();
	void move_room_left();
	void load_room(Engine::EntityManager<Component>* manager);
	void init_next_level();
	bool reload_level{true};
	static LevelSingleton* get_instance();
	std::string get_current_room_name_from_current_level() const;
	RoomComponent* get_current_room() const;
	uint8_t get_starting_room();
	uint8_t get_current_room_number() const;
};
