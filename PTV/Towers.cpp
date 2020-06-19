#include "Header.h"

void Towers::setSprite(sf::Sprite sprite) {
	this->tower = sprite;
}

sf::Sprite Towers::getSprite() {
	return this->tower;
}

void Towers::setPosition(sf::Vector2f position) {
	this->tower.setPosition(position);
};

void Towers::setCost(int cost) {
	this->cost = cost;
}

int Towers::getCost(){
	return this->cost;
}

void Towers::setDamage(int damage) {
	this->damage = damage;
}

int Towers::getDamage() {
	return this->damage;
}

void Towers::setRange(float range) {
	this->range = range;
}

float Towers::getRange() {
	return this->range;
}

void Towers::levelUp() {
	this->level++;
	this->setCost(this->getCost() * 1.5);
	this->setDamage(this->getDamage() * 1.2);
	this->setRange(this->getRange() * 1.15);
}

ArrowTower::ArrowTower() {
	texture.loadFromFile("Resources/assets.psd");
	sf::Sprite arrowTower(texture, sf::IntRect(93, 92, 80, 80));
	this->setSprite(arrowTower);

	this->level = 1;
	this->setCost(40);
	this->hitsFlying = true;
}

CannonTower::CannonTower() {
	texture.loadFromFile("Resources/assets.psd");
	sf::Sprite cannonTower(texture, sf::IntRect(93, 251, 80, 80));
	this->setSprite(cannonTower);

	this->level = 1;
	this->setCost(70);
}

MagicTower::MagicTower() {
	texture.loadFromFile("Resources/assets.psd");
	sf::Sprite magicTower(texture, sf::IntRect(93, 411, 80, 84));
	this->setSprite(magicTower);

	this->level = 1;
	this->setCost(55);
	this->hitsFlying = true;
	this->hitsThroughArmor = true;
}