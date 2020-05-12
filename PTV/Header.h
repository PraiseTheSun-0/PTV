#pragma once
#include <SFML/Graphics.hpp>
#include "StandardCursor.hpp"

enum game_state {
	START_SCREEN,
	MAIN_MENU,
	PLAYING_SOLO,
	PLAYING_TWO,
	QUIT
};

bool isMouseIn(sf::RenderWindow &window, sf::RectangleShape &rectangle);