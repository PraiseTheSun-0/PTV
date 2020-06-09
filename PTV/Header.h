#pragma once
#include <SFML/Graphics.hpp>
#include "StandardCursor.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <iostream>

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

class Attackers {
public:
	/*enum {
		BAT,
		ORC,
		GOBLIN
	};*/
	int numOfEnemies = 10;
	int HP = 100;
	float movespeed = 0.025;
	bool armored = false, flying = false;
	struct enemies{
		sf::Sprite enemy[3];
		bool alive;

	};
	std::vector<enemies>monsters;
	void spawn(sf::Sprite enemy[3], sf::RenderWindow& window, Game* game); 
	void prepareWave(int numberOfEnemies, sf::Sprite enemy[]);

};



bool isMouseIn(sf::RenderWindow &window, sf::RectangleShape &rectangle);
bool cmpf(float, float, float);