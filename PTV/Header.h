#pragma once
#include <SFML/Graphics.hpp>
#include "StandardCursor.hpp"
#include <vector>

enum GAME_STATE {
	START_SCREEN,
	MAIN_MENU,
	PLAYING_SOLO,
	PLAYING_TWO,
	QUIT
};

class Game {
public:
	sf::Clock animation;
	sf::Clock waveTimer;
	sf::Event event;
	void run();
};

class MapLayout {
public:
	struct cells {
		std::vector<sf::RectangleShape> tiles;
		std::vector<bool> isPath;
		std::vector<bool> isTower;
	}Tiles;
	
	float bound_x = 5, bound_y = 10;

	MapLayout(GAME_STATE);
	

};

class Enemies {
public:
	enum {
		BAT,
		GOBLIN,
		ORC
	};

	void spawn(sf::RenderWindow &window, sf::Sprite &enemies1, sf::Sprite &enemies2, sf::Sprite &enemies3, Game *game);
};

bool isMouseIn(sf::RenderWindow &window, sf::RectangleShape &rectangle);