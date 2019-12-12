#pragma once
#include <string>

class LevelSingleton
{
private:
	static LevelSingleton* instance;
	LevelSingleton();
	int current_level_index;
	std::string levels[3][3] = { "lazy", "second", "third", "two_first", "two_second", "two_third", "third_first", "third_second", "third_third" };
public:
	static LevelSingleton* get_instance();
	std::string get_current_room_name_from_current_level(const int current_room_index) const;
	void init_next_level();
	bool reload_level;
	int get_current_level_number() const;
	void delete_instance();
};