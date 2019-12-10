#include "LevelSingleton.h"
#include "RoomSingleton.h"
#include <fstream>
#include <filesystem>

LevelSingleton::LevelSingleton() {
	current_room_ = 0;
}

LevelSingleton* LevelSingleton::instance = 0;

LevelSingleton* LevelSingleton::get_instance()
{
	if (instance == nullptr) {
		instance = new LevelSingleton();
	}
	return instance;
}

void LevelSingleton::load_dungeon(const std::string& path)
{
	std::ifstream map("./assets/Levels/Dungeons/" + path);
	if (map.fail())
	{
		return;
	}
	int last_row_index{ -5 };
	for (int i = 0; i < 25; ++i)
	{
		//Determines what kind of room will be made
		std::string room_name{};

		//Read room name from map file
		map >> room_name;

		//If the was a problem in reading the map
		if (map.fail())
		{
			//Stop loading map	
			return;
		}
		if (room_name != "0")
		{
			auto new_room = std::make_unique<RoomComponent>(room_name, i);
			if (last_row_index >= 0)
			{
				auto& top_room = level_rooms_.at(path)[last_row_index];
				if (top_room != nullptr)
				{
					top_room->down = new_room.get();
					new_room->top = top_room.get();
				}
			}
			if (i > 0)
			{
				auto& left_room = level_rooms_.at(path)[i - 1];
				if (left_room != nullptr)
				{
					left_room->right = new_room.get();
					new_room->left = left_room.get();
				}
			}
			level_rooms_[path].push_back(std::move(new_room));
		}
		else
		{
			level_rooms_[path].push_back(nullptr);
		}
		++last_row_index;
	}
	if (std::adjacent_find(level_rooms_[path].begin(), level_rooms_[path].end(), std::not_equal_to<>()) == level_rooms_[path].end())
	{
		level_rooms_.erase(path);
	}
	map.close();
}

void LevelSingleton::load_all_dungeons()
{
	bool first_level{false};
	for (const auto& entry : std::filesystem::directory_iterator("./assets/Levels/Dungeons/"))
	{
		if (entry.path().extension().string() == ".dungeon")
		{
			if (!first_level) {
				current_level_ = entry.path().filename().string();
				first_level = true;
			}
			load_dungeon(entry.path().filename().string());
		}
	}
	get_starting_room();
}

void LevelSingleton::move_room_up()
{
	current_room_ -= 5;
}

void LevelSingleton::move_room_right()
{
	current_room_ += 1;
}

void LevelSingleton::move_room_down()
{
	current_room_ += 5;
}

void LevelSingleton::move_room_left()
{
	current_room_ -= 1;
}

void LevelSingleton::load_room(Engine::EntityManager<Component>* manager)
{
	RoomSingleton::get_instance()->load_room(manager, level_rooms_.at(current_level_)[current_room_].get());
}

std::string LevelSingleton::get_current_room_name_from_current_level() const {
	return level_rooms_.at(current_level_).at(current_room_)->room_name;
}

RoomComponent* LevelSingleton::get_current_room() const
{
	return level_rooms_.at(current_level_).at(current_room_).get();
}

void LevelSingleton::init_next_level() {
	if (current_room_ < 2) {
		current_room_++;
		RoomSingleton::get_instance()->init_first_room();
	}
}

uint8_t LevelSingleton::get_starting_room()
{
	if (reload_level)
	{
		const int length = level_rooms_.at(current_level_).size();
		uint8_t starting_room{ 0 };
		for (auto i = 0; i < length; ++i)
		{
			if (level_rooms_.at(current_level_)[i] != nullptr)
			{
				starting_room = i;
				break;
			}
		}
		current_room_ = starting_room;
		return starting_room_ = starting_room;
	}
	return starting_room_;

}



uint8_t LevelSingleton::get_current_room_number() const {
	return current_room_;
}
