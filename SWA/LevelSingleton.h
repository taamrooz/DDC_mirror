#pragma once
#include <string>
#include <vector>
#include "RoomComponent.h"
#include <map>
#include <memory>

class LevelSingleton
{
private:
	static LevelSingleton* instance;
	LevelSingleton();
	int current_level_index_{0};
	uint8_t starting_room_;
	std::string current_level_;
	std::string levels[3][3] = { "lazy", "second", "third", "two_first", "two_second", "two_third", "third_first", "third_second", "third_third" };
	std::map<std::string, std::vector<std::unique_ptr<RoomComponent>>> level_rooms_;
public:
	static LevelSingleton* get_instance();
	void load_dungeon(const std::string path);
	void load_all_dungeons();
	std::string get_current_room_name_from_current_level(const int current_room_index) const;
	void init_next_level();
	bool reload_level{true};
	uint8_t get_starting_room();
	int get_current_level_number() const;
};
