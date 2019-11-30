#include "TileSetSingleton.h"

TileSetSingleton::TileSetSingleton() {
	int x = 0;
	int y = 0;
	for (int i = 0; i < k_total_tiles_; ++i) {
		std::vector<int> myRow(4);
		tiletypes.push_back(myRow);
		tiletypes[i][0] = x;
		tiletypes[i][1] = y;
		tiletypes[i][2] = k_tile_width_;
		tiletypes[i][3] = k_tile_height_;

		y += k_tile_height_;
		if (y >= 448)
		{
			y = 0;
			x += k_tile_width_;
		}
	}

	path = "Tileset.png";
	reload = true;
}

TileSetSingleton* TileSetSingleton::instance = 0;

//Returns an instance of the TileSet
TileSetSingleton* TileSetSingleton::get_instance()
{
	if (instance == 0) {
		instance = new TileSetSingleton();
	}
	return instance;
}