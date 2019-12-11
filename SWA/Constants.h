#pragma once

struct Constants
{
	constexpr static int k_window_width = 1280;
	constexpr static int k_window_height = 960;
	constexpr static int k_level_width = 1280;
	constexpr static int k_total_tiles = 300;
	constexpr static int k_tile_height = 64;
	constexpr static int k_tile_width = 64;
	constexpr static int k_total_sprites = 49;
	constexpr static int k_collision_tiles[37] = { 2, 3, 4, 5 ,6 ,9 ,11 ,12 , 13 ,16, 17, 18 ,19 ,20 ,23 ,24 , 25 ,26 ,27 ,30 ,31 ,32 ,33 ,34, 36 ,37 ,38 ,39 ,40, 41, 42, 43, 44, 45, 46, 47, 48 };
	inline const static std::string k_map_suffix{ ".map" };
	inline const static std::string k_object_suffix{ ".object" };
	inline const static std::string k_dungeon_suffix{ ".dungeon" };
};