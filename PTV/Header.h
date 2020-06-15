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

enum DIRECTION {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum ENEMY_TYPE {
	BAT,
	ORC,
	GOBLIN
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

class BuildMenu : public sf::Drawable {
public:
	sf::Texture texture;
	sf::Sprite menuBackground;

	BuildMenu();
};

class Attackers {
public:
	int numOfEnemies[3] = {7, 3, 12};
	int timeBetweenSpawn;
	struct enemies {
		sf::Sprite enemy[3];
		bool alive;
		bool checkPointReached[9] = { 0 };
		int HP = 100;
		float movespeed = 0.15;
		int livesTaken = 1;
		bool armored = false, flying = false;

	};
	std::vector<enemies>monsters;
	void spawn(sf::Sprite enemy[3], sf::RenderWindow& window, Game* game); 
	void prepareWave(ENEMY_TYPE enemyType, sf::Sprite enemy[], sf::Vector2f spawn, float waveMultiplier);

};

class Towers {
	sf::Sprite tower;
	int cost;
	float range;
	int damage;
	bool hitsFlying;
	bool hitsThroughArmor;
public:
	Towers(sf::Sprite sprite);
	void setSprite(sf::Sprite sprite);
	sf::Sprite getSprite();
};


bool isMouseIn(sf::RenderWindow &window, sf::RectangleShape &rectangle);
bool cmpf(float, float, float);
void move(sf::Sprite enemy[3], float movespeed, DIRECTION direction);