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

class HPBar : public sf::Drawable {
public:
	sf::RectangleShape back, max, current;
	HPBar();
	void update(int current, int max, sf::Sprite);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(back);
		target.draw(max);
		target.draw(current);
	}
};

class Attackers {
public:
	int numOfEnemies[3] = {7, 3, 12};
	int timeBetweenSpawn;
	struct enemies {
		sf::Sprite enemy[3];
		bool alive;
		bool checkPointReached[9] = { 0 };
		int bounty = 10;
		int HP = 100;
		int currentHP;
		float movespeed = 1.0f;
		int livesTaken = 1;
		bool armored = false, flying = false;
		HPBar hpBar;
		bool killed = false;
		bool spawned = false;
	};
	std::vector<enemies>monsters;
	void spawn(sf::Sprite enemy[3], sf::RenderWindow& window, Game* game); 
	void prepareWave(ENEMY_TYPE enemyType, sf::Sprite enemy[], sf::Vector2f spawn, float waveMultiplier);

};

class Bullet {
public:
	sf::Sprite projectile;
	bool isBeam = false, isProjectile = false;
	float speed = 150.0f;
	sf::Vector2f from;
	sf::Vector2f target;
	sf::Clock time;
	bool reached = false;
	int targetId;
	Bullet(sf::Sprite, sf::Sprite from, sf::Sprite target, int target_id);
	void update();
};

class Towers {
	TOWER_TYPE towerType;
	sf::Sprite tower;
	int cost;
	float range = 160.0f;
	int damage;
	float attackSpeed = 0.7f;

public:
	int level;
	int towerId;
	bool hasSplash = false;
	float splashDamage = 0.3;
	bool hitsFlying = false;
	bool hitsThroughArmor = false;
	bool upgraded = false;
	bool lockedOn = false;
	std::vector<int> targetId;
	int hitsTargets = 1;
	sf::Clock timer;
	sf::Sprite projectile;
	std::vector<Bullet*> bullets;

	virtual void setTowerType(TOWER_TYPE tower_type);
	virtual TOWER_TYPE getTowerType();

	virtual void setDamage(int damage);
	virtual int getDamage();

	virtual void setAttackSpeed(float attack_speed);
	virtual float getAttackSpeed();

	virtual void setRange(float range);
	virtual float getRange();

	sf::Texture texture;
	virtual void setPosition(sf::Vector2f position);
	virtual void setSprite(sf::Sprite sprite);
	virtual sf::Sprite getSprite();

	void findTarget(Attackers enemies);
	void loseTarget();
	virtual void shoot(Attackers &enemies) {}
	void updateBullets(sf::RenderWindow& window, Attackers& enemies);

	virtual void setCost(int cost);
	virtual int getCost();

	void levelUp(int* gold);
	virtual void upgrade1(int* gold) {}
	virtual void upgrade2(int* gold) {}
};

class ArrowTower: public Towers {
public:
	ArrowTower();
	void upgrade1(int* gold) override;
	void upgrade2(int* gold) override;
	void shoot(Attackers& enemies) override;
};

class CannonTower : public Towers {
public:
	CannonTower();
	void upgrade1(int* gold) override;
	void upgrade2(int* gold) override;
	void shoot(Attackers& enemies) override;
};


class MagicTower : public Towers {
public:
	MagicTower();
	void upgrade1(int* gold) override;
	void upgrade2(int* gold) override;
	void shoot(Attackers &enemies) override;
};

class BuildMenu : public sf::Drawable {
public:
	sf::Font font;
	sf::Texture texture;
	sf::Sprite menuBackground;
	sf::Text text1, text2, text3, text4;
	sf::RectangleShape menu, button1, button2, button3;
	sf::Vector2f buildPosition;
	int tile_id;
	int tower_index;

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
	void isTower(std::vector<Towers*>& towers, int tower_id);
	void sell(int* gold, std::vector<Towers*>& towers, MapLayout &map_layout);
};

bool isMouseIn(sf::RenderWindow &window, sf::RectangleShape &rectangle);
bool cmpf(float, float, float);
void move(sf::Sprite enemy[3], float movespeed, DIRECTION direction);
float findRange(sf::Sprite tower, sf::Sprite enemy);