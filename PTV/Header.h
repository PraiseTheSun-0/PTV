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

enum TOWER_TYPE {
	ARROW,
	SPLASH,
	MAGIC
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
	int numOfEnemies[3] = {7, 3, 12};
	int timeBetweenSpawn;
	struct enemies {
		sf::Sprite enemy[3];
		bool alive;
		bool checkPointReached[9] = { 0 };
		int bounty = 8;
		int HP = 100;
		float movespeed = 0.1f;
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

public:
	int level;
	int towerId;
	bool hitsFlying = false;
	bool hitsThroughArmor = false;

	void setDamage(int damage);
	int getDamage();

	void setRange(float range);
	float getRange();

	sf::Texture texture;
	void setPosition(sf::Vector2f position);
	void setSprite(sf::Sprite sprite);
	sf::Sprite getSprite();

	void setCost(int cost);
	int getCost();

	void levelUp();
	void upgrade1();
	void upgarde2();
};

class ArrowTower: public Towers {
public:
	ArrowTower();

};

class CannonTower : public Towers {
public:
	CannonTower();

};


class MagicTower : public Towers {
public:
	MagicTower();

};

class BuildMenu : public sf::Drawable {
public:
	sf::Font font;
	sf::Texture texture;
	sf::Sprite menuBackground;
	sf::Text text1, text2, text3, text4;
	sf::RectangleShape button1, button2, button3;
	sf::Vector2f buildPosition;
	int tile_id;

	BuildMenu();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(menuBackground);
		target.draw(text1);
		target.draw(text2);
		target.draw(text3);
		target.draw(text4);
	}
	void isNotTower(sf::RectangleShape build_position, int tileId);
	void build(int* gold, std::vector<Towers*> &towers, TOWER_TYPE tower_type, MapLayout &map_layout);
};

bool isMouseIn(sf::RenderWindow &window, sf::RectangleShape &rectangle);
bool cmpf(float, float, float);
void move(sf::Sprite enemy[3], float movespeed, DIRECTION direction);