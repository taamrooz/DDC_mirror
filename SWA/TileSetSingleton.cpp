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

		y += 80;
		if (y >= 240)
		{
			y = 0;
			x += 80;
		}
	}

	path = "tiles.png";
	reload = true;
}

TileSetSingleton* TileSetSingleton::instance = 0;

TileSetSingleton* TileSetSingleton::get_instance()
{
	if (instance == 0) {
		instance = new TileSetSingleton();
	}
	return instance;
}