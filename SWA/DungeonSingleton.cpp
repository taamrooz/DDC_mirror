#include "DungeonSingleton.h"
#include "RoomSingleton.h"
#include <fstream>
#include <filesystem>
#include "Constants.h"

DungeonSingleton::DungeonSingleton() {
	current_room_ = 0;
}

DungeonSingleton* DungeonSingleton::instance = 0;

DungeonSingleton* DungeonSingleton::get_instance()
{
	if (instance == nullptr) {
		instance = new DungeonSingleton();
	}
	return instance;
}

void DungeonSingleton::load_dungeon(const std::string& path)
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
				auto& top_room = level_rooms_[last_row_index];
				if (top_room != nullptr)
				{
					top_room->down = new_room.get();
					new_room->top = top_room.get();
				}
			}
			if (i > 0)
			{
				auto& left_room = level_rooms_[i - 1];
				if (left_room != nullptr)
				{
					left_room->right = new_room.get();
					new_room->left = left_room.get();
				}
			}
			level_rooms_.push_back(std::move(new_room));
		}
		else
		{
			level_rooms_.push_back(nullptr);
		}
		++last_row_index;
	}
	map.close();
}

void DungeonSingleton::load_all_dungeons()
{
	for (const auto& entry : std::filesystem::directory_iterator("./assets/Levels/Dungeons/"))
	{
		if (entry.path().extension().string() == Constants::k_dungeon_suffix)
		{
			levels_.push_back(entry.path().filename().string());
		}
	}
	load_dungeon(levels_.front());

	get_starting_room();
}

void DungeonSingleton::move_room(Direction dir)
{
	switch (dir)
	{
	case down: move_room_down(); break;
	case up: move_room_up(); break;
	case left: move_room_left(); break;
	case right: move_room_right(); break;
	}
}


void DungeonSingleton::move_room_up()
{
	if (level_rooms_[current_room_ - 5] != nullptr)
	{
		current_room_ -= 5;
		RoomSingleton::get_instance()->reload_room = true;
		RoomSingleton::get_instance()->dir = up;
	}
}

void DungeonSingleton::move_room_right()
{
	if (level_rooms_[current_room_ + 1] != nullptr)
	{
		current_room_ += 1;
		RoomSingleton::get_instance()->reload_room = true;
		RoomSingleton::get_instance()->dir = right;
	}
}

void DungeonSingleton::move_room_down()
{
	if (level_rooms_[current_room_ + 5] != nullptr)
	{
		current_room_ += 5;
		RoomSingleton::get_instance()->reload_room = true;
		RoomSingleton::get_instance()->dir = down;
	}
}

void DungeonSingleton::move_room_left()
{
	if (level_rooms_[current_room_ - 1] != nullptr)
	{
		current_room_ -= 1;
		RoomSingleton::get_instance()->reload_room = true;
		RoomSingleton::get_instance()->dir = left;
	}
}

void DungeonSingleton::load_room(Engine::EntityManager<Component>* manager)
{
	RoomSingleton::get_instance()->load_room(manager, level_rooms_[current_room_].get());
}

void DungeonSingleton::move_dungeon_down()
{
	if (levels_.size() - 1 > current_level_)
	{
		current_level_++;
		get_starting_room();
		load_dungeon(levels_[current_level_]);
	}
}

RoomComponent* DungeonSingleton::get_current_room() const
{
	return level_rooms_.at(current_room_).get();
}

std::string DungeonSingleton::get_current_level_path() const
{
	return levels_.at(current_level_);
}

uint32_t DungeonSingleton::get_current_level() const
{
	return current_level_;
}

uint8_t DungeonSingleton::get_starting_room()
{
	const int length = level_rooms_.size();
	uint8_t starting_room{ 0 };
	for (auto i = 0; i < length; ++i)
	{
		if (level_rooms_[i] != nullptr)
		{
			starting_room = i;
			break;
		}
	}
	return current_room_ = starting_room;
}



uint8_t DungeonSingleton::get_current_room_number() const {
	return current_room_;
}

bool DungeonSingleton::is_last_dungeon() const
{
	return levels_.size() - 1 == current_level_;
}
