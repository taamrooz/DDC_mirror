#pragma once
#include <Texture.h>
#include <vector>

class TileSetSingleton
{
private:
	const int k_tile_width_ = 64;
	const int k_tile_height_ = 64;
	const int k_total_tiles_ = 49;
	/* The instance will be stored here. */
	static TileSetSingleton* instance;

	/* Private constructor to prevent instancing. */
	TileSetSingleton();
public:
	Texture* tilemap;
	bool reload;
	std::string path;
	std::vector<std::vector<int>> tiletypes;
	static TileSetSingleton* get_instance();
};