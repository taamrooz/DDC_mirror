#include "TileSetSingleton.h"
#include "Constants.h"

TileSetSingleton::TileSetSingleton() {
	int x = 0;
	int y = 0;
	for (int i = 0; i < Constants::k_total_tiles; ++i) {
		std::vector<int> myRow(4);
		tiletypes.push_back(myRow);
		tiletypes[i][0] = x;
		tiletypes[i][1] = y;
		tiletypes[i][2] = Constants::k_tile_width;
		tiletypes[i][3] = Constants::k_tile_height;

		y += Constants::k_tile_height;
		if (y >= 448)
		{
			y = 0;
			x += Constants::k_tile_width;
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

void TileSetSingleton::delete_instance()
{
	delete instance;
	instance = nullptr;
}
