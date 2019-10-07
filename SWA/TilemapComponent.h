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
			tiletypes[i].push_back(x);
			tiletypes[i].push_back(y);
			tiletypes[i].push_back(80);
			tiletypes[i].push_back(80);

			x += 80;

			//If we've gone too far
			if (x >= 320)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += 80;
			}
		}

		path = "tiles.png";
		reload = true;
	};
};