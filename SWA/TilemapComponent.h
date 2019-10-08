#pragma once
#include "Component.h"
#include <Texture.h>

struct TilemapComponent : Component
{
	Texture* tilemap;
	bool reload;
	std::string path;
	std::vector<std::vector<int>> tiletypes;

	TilemapComponent() {
		int x = 0;
		int y = 0;
		for (int i = 0; i < 12; ++i) {
			std::vector<int> myRow(4);
			tiletypes.push_back(myRow);
			tiletypes[i][0] = x;
			tiletypes[i][1] = y;
			tiletypes[i][2] = 80;
			tiletypes[i][3] = 80;

			y += 80;

			//If we've gone too far
			if (y >= 240)
			{
				//Move back
				y = 0;

				//Move to the next row
				x += 80;
			}
		}

		path = "tiles.png";
		reload = true;
	};
};