#include "Header.h"

MapLayout::MapLayout(GAME_STATE game_state) {
	int tile_number = 0;

	for (int i = 0; i < 209; i++) {
		Tiles.tiles.push_back(sf::RectangleShape(sf::Vector2f(84, 81)));
		Tiles.isPath.push_back(false);
		Tiles.isTower.push_back(false);

	}

	if (game_state == PLAYING_SOLO) {
		for (float k = bound_y; k < 900; k += 81) {
			for (float i = bound_x; i < 1600; i += 84) {
				Tiles.tiles[tile_number].setPosition(sf::Vector2f(i, k));
				tile_number++;
			}
		}
		for (int i = 19; i < 22; i++)Tiles.isPath[i] = true;
		Tiles.isPath[37] = true;  Tiles.isPath[36] = true; Tiles.isPath[40] = true;
		for (int i = 43; i < 57; i++)Tiles.isPath[i] = true;
		Tiles.isPath[59] = true; Tiles.isPath[62] = true; Tiles.isPath[75] = true; Tiles.isPath[74] = true; Tiles.isPath[78] = true; Tiles.isPath[81] = true;
		for (int i = 86; i < 91; i++)Tiles.isPath[i] = true;
		Tiles.isPath[97] = true; Tiles.isPath[100] = true; Tiles.isPath[105] = true; Tiles.isPath[109] = true; Tiles.isPath[116] = true;
		for (int i = 119; i < 125; i++)Tiles.isPath[i] = true;
		Tiles.isPath[128] = true; Tiles.isPath[135] = true; Tiles.isPath[105] = true; Tiles.isPath[147] = true;
		for (int i = 154; i < 167; i++)Tiles.isPath[i] = true;
	}

	if (game_state == PLAYING_TWO) {	//todo
		for (float k = bound_y; k < 900; k += 81) {
			for (float i = bound_x; i < 1600; i += 84) {
				Tiles.tiles[tile_number].setPosition(sf::Vector2f(i, k));
				tile_number++;
			}
		}

	}

}
