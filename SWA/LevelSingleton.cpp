#include "LevelSingleton.h"
#include "RoomSingleton.h"

LevelSingleton::LevelSingleton() {
	current_level_index = 0;
	reload_level = true;
}

LevelSingleton* LevelSingleton::instance = 0;

LevelSingleton* LevelSingleton::get_instance()
{
	if (instance == 0) {
		instance = new LevelSingleton();
	}
	return instance;
}

std::string LevelSingleton::get_current_room_name_from_current_level(const int current_room_index) const {
	return levels[current_level_index][current_room_index];
}

void LevelSingleton::init_next_level() {
	if (current_level_index < 2) {
		current_level_index++;
		RoomSingleton::get_instance()->init_first_room();
	}
}

int LevelSingleton::get_current_level_number() const {
	return (1 + current_level_index);
}

void LevelSingleton::delete_instance()
{
	delete instance;
	instance = nullptr;
}
